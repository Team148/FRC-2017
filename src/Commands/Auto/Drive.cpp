#include "Drive.h"


Drive::Drive(double inches, double velocity) {
	Requires(Drivetrain::GetInstance());
	m_travelDistance  = inches; //How far we want to go in inches
	m_cruiseVelocity = velocity;

	if(inches<0) {m_isReverse=true;}
	log = new Logger("DriveCommandLog");
}

// Called just before this Command runs the first time
void Drive::Initialize() {
	log->Start();
	//reset isFinished
	m_isFinished=0;

	//check where we pointing
	m_initangle = Drivetrain::GetInstance()->GetAngle();

	//check that the Drivetrain is in closed loop
	if(!Drivetrain::GetInstance()->isClosedLoop())
		Drivetrain::GetInstance()->configClosedLoop();

	//ensure queue is empty
	while(!m_output.empty())
		m_output.pop();

	while(!m_dist.empty())
		m_dist.pop();

	//to begin, check if a triangle or trapezoid profile is needed.
	float accel_dist = 0.5*m_cruiseVelocity*m_cruiseVelocity/m_maxAccelRate;
	int accel_segments = ceil(m_cruiseVelocity/m_maxAccelRate/m_dt);

	double accel_time = m_cruiseVelocity/m_maxAccelRate;
	double accel_cruise_time = m_travelDistance/m_cruiseVelocity;

	double decel_time = -m_cruiseVelocity/m_maxDecelRate;
	float decel_dist = -0.5*m_cruiseVelocity*m_cruiseVelocity/m_maxDecelRate;
	int decel_segments = ceil(abs(m_cruiseVelocity/m_maxDecelRate/m_dt));
	double end_time = accel_cruise_time + decel_time;

	bool isTriangular=0;
	float max_velocity;
	if(accel_dist*2 > m_travelDistance) {
		//we will never reach the requested speed, so a triangle profile is generated
		cout << "info: generating Triangle profile" << endl;
		isTriangular=true;
		max_velocity = pow(2 * m_maxAccelRate * (m_travelDistance/2),0.5);
		accel_time = max_velocity/m_maxAccelRate;
		accel_cruise_time = accel_time;
		decel_time = -max_velocity/m_maxDecelRate;
		accel_segments = ceil(max_velocity/m_maxAccelRate/m_dt);
		decel_segments = ceil(-max_velocity/m_maxDecelRate/m_dt);
		end_time = accel_time + decel_time;
	}

	log->AddtoBuffer("accel_segments", accel_segments);
	log->AddtoBuffer("decel_segments", decel_segments);


	//generate acceleration curve
	for(int i = 0;i <= accel_segments;i++) {
		double t = m_dt*i;
	    m_output.push(m_maxAccelRate*t);
	    m_dist.push(0.5*m_maxAccelRate*t*t);

	    //Log
	    log->AddtoBuffer("Vel", m_maxAccelRate*t);
	    log->AddtoBuffer("Dist", 0.5*m_maxAccelRate*t*t);
	 }
	float top_speed_reached = m_output.back();
	float acc_distance = m_dist.back();

	//If needed, generate hold curve
	float hold_distance = 0;
	float hold_time = 0;
	int hold_segments = 0;
	if(!isTriangular) {
		hold_distance = m_travelDistance - (accel_dist + decel_dist);
		hold_time = hold_distance/m_cruiseVelocity;
		hold_segments = hold_time / m_dt;
		//cout << "Hold Distance: " << hold_distance << endl;
		//cout << "hold Time: " << hold_time << endl;
		//generate the hold
		for(int y = 1;y <= hold_segments;y++) {
			double t = m_dt*y;
			m_output.push(m_cruiseVelocity);
			m_dist.push(acc_distance+m_cruiseVelocity*t);

			//LOG
			log->AddtoBuffer("Vel",m_cruiseVelocity);
			log->AddtoBuffer("Dist", acc_distance+m_cruiseVelocity*t);
		}
	}
	float initial_d = m_dist.back();


	//generate deceleration curve
	for(int i=1 ;i < decel_segments;i++) {
		float t = m_dt*i;
		float curr_t = t + accel_cruise_time;
	    // v = u + at
	    float velocity = top_speed_reached+(m_maxDecelRate*t);
	    float dist = m_travelDistance + 0.5*m_maxDecelRate*pow(curr_t-end_time,2);								//very negative
	    if(velocity > 0)
	    	m_output.push(velocity);
	    	m_dist.push(dist);

	    	//LOG
	    	log->AddtoBuffer("Vel",velocity);
	    	log->AddtoBuffer("Dist", dist);
	 }
	 //push last point
	 m_output.push(0);
	 m_dist.push(m_travelDistance);
	 log->AddtoBuffer("Vel",0);
	 log->AddtoBuffer("Dist", m_travelDistance);

	 log->WriteBuffertoFile();
	 log->CloseFile();

	cout<<"info: generated profile with"<< accel_segments+hold_segments+decel_segments << " Points. time: " << end_time <<"sec"<< endl;
}


// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {

	float cur_vel = m_output.front();
	float cur_dist = m_dist.front();

	//after setting, remove from queue
	m_output.pop();
	m_dist.pop();


	//find actual velocity(rpm)
	int act_lvel = Drivetrain::GetInstance()->GetLeftVelocity();
	int act_rvel = Drivetrain::GetInstance()->GetRightVelocity();

	//convert IPS to RPM and account
	cur_vel = Drivetrain::GetInstance()->IPStoRPM(cur_vel);

	//compute heading hold compensation
	float cur_angle = Drivetrain::GetInstance()->GetAngle();
	float cur_angle_err = cur_angle - m_initangle;
	float gyro_comp = DRIVE_GYRO_P*cur_angle_err;

	//Find left and right velocity error
	int vel_l_error = act_lvel - cur_vel;
	int vel_2_error = act_rvel - cur_vel;



	//SetLeft and SetRight to current queue with gyro compensation
	Drivetrain::GetInstance()->SetLeft(cur_vel-gyro_comp);
	Drivetrain::GetInstance()->SetRight(cur_vel+gyro_comp);

	//for Testing
	cout <<"info: set drivetrain to " << cur_vel <<" RPM" << endl;
	cout <<"info: heading error is " << cur_angle_err << "Degrees" << endl;

	//once the queue is empty, set isFinished
	if(m_output.empty())
		m_isFinished=true;
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void Drive::End() {
	Drivetrain::GetInstance()->SetLeft(0);
	Drivetrain::GetInstance()->SetRight(0);
	cout <<"info: set drivetrain to " << 0 <<" RPM" << endl;

	//empty the queue if interrupted
	while(!m_output.empty())
		m_output.pop();

	while(!m_dist.empty())
		m_dist.pop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {
	End();
}
