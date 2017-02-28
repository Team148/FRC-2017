#include "Drive.h"


Drive::Drive(double inches, double velocity) {
	Requires(Drivetrain::GetInstance());
	m_travelDistance  = inches; //How far we want to go in inches
	m_cruiseVelocity = velocity;

	if(inches<0) {
		m_isReverse=true;
		m_travelDistance = -m_travelDistance;
	}
	log = new Logger("DriveProfile-Log");
}

// Called just before this Command runs the first time
void Drive::Initialize() {
	log->Start();
	//reset isFinished
	m_isFinished=0;
	float accel_dist,hold_time,hold_segments=0;
	bool isTriangular=0;


	//check where we pointing
	m_initangle = Drivetrain::GetInstance()->GetAngle();

	//reset encoder distance
	Drivetrain::GetInstance()->ZeroSensors();

	//check that the Drivetrain is in closed loop
	if(!Drivetrain::GetInstance()->isClosedLoop())
		Drivetrain::GetInstance()->configClosedLoop();

	//ensure queue is empty
	while(!m_output.empty())
		m_output.pop();

	while(!m_dist.empty())
		m_dist.pop();

	//to begin, calculate the time we would need to accelerate to the theoretical max speed.
	float accel_time = sqrt(m_travelDistance/m_maxAccelRate);
	float max_vel = m_maxAccelRate*accel_time;


   if(max_vel>m_cruiseVelocity) {
    max_vel = m_cruiseVelocity;
    cout <<"trapezoid" << endl;
    accel_time = m_cruiseVelocity/m_maxAccelRate;
    accel_dist = 0.5*m_maxAccelRate*pow(accel_time,2);

    hold_time = (m_travelDistance-accel_dist-accel_dist)/m_cruiseVelocity;
    //hold_dist = m_travelDistance - accel_dist - accel_dist;
    hold_segments = ceil(hold_time/m_dt);
   }
   else {
    cout <<"triangle" << endl;
    isTriangular=true;
    accel_dist = 0.5*m_maxAccelRate*pow(accel_time,2);
   }

	//calculate the segments needed
    float end_time = accel_time + accel_time + hold_time;
    int accel_segments = ceil(accel_time/m_dt);
	int decel_segments = accel_segments;

	log->AddtoBuffer("accel_segments", accel_segments);
	log->AddtoBuffer("decel_segments", decel_segments);


	//generate acceleration curve
	for(int i = 0;i < accel_segments;i++) {
		double t = m_dt*i;
	    float v = (m_maxAccelRate*t);
	    float d = (0.5*m_maxAccelRate*t*t);

		if(m_isReverse) {
        v=-v;
        d = -d;
        }

	    m_output.push(v);
	    m_dist.push(d);
	    //Log
	    log->AddtoBuffer("Vel", v);
	    log->AddtoBuffer("Dist", d);
	 }


	//if needed, generate hold
	if(!isTriangular) {
		for(int i = 0;i <= hold_segments;i++) {
			double t = m_dt*i;
			float v = (m_cruiseVelocity);
			float d = (accel_dist+m_cruiseVelocity*t);

			if(m_isReverse) {
				v=-v;
				d = -d;
			}

			m_output.push(v);
			m_dist.push(d);
			//LOG
			log->AddtoBuffer("Vel",v);
			log->AddtoBuffer("Dist", d);
		}
	}

	//generate deceleration curve
	for(int i=1 ;i < decel_segments;i++) {
		float t = m_dt*i;
		float curr_t = t + accel_time + hold_time;
	    float v = max_vel-(m_maxAccelRate*t);
	    float d = m_travelDistance - 0.5*m_maxAccelRate*pow(curr_t-end_time,2);								//very negative

		if(m_isReverse) {
			v=-v;
			d = -d;
		}

	    m_output.push(v);
	    m_dist.push(d);

	    //LOG
	    log->AddtoBuffer("Vel",v);
	    log->AddtoBuffer("Dist", d);
	 }
	 //push last point
	 m_output.push(0);

	 if(m_isReverse)
		m_dist.push(-m_travelDistance);
	else
		m_dist.push(m_travelDistance);

	 log->AddtoBuffer("Vel",0);
	 log->AddtoBuffer("Dist", m_travelDistance);

	 log->WriteBuffertoFile();
	 //log->CloseFile();

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

	//find actual distance and convert to inches
	int act_ldist = Drivetrain::GetInstance()->RotationtoInch(Drivetrain::GetInstance()->GetLeftDistance());
	int act_rdist = Drivetrain::GetInstance()->RotationtoInch(Drivetrain::GetInstance()->GetRightDistance());

	//convert IPS to RPM and account
	cur_vel = Drivetrain::GetInstance()->IPStoRPM(cur_vel);



	//Find left and right velocity error
	float vel_lerr = cur_vel-act_lvel;
	float vel_rerr = cur_vel-act_rvel;
	float vel_lcomp = DRIVE_VELOCITY_P*vel_lerr;
	float vel_rcomp = DRIVE_VELOCITY_P*vel_rerr;

	//compute heading hold compensation
	float cur_angle = Drivetrain::GetInstance()->GetAngle();
	float cur_angle_err = cur_angle - m_initangle;
	float gyro_comp = DRIVE_GYRO_P*cur_angle_err;



	//SetLeft and SetRight to current queue with gyro compensation
	Drivetrain::GetInstance()->SetLeft((cur_vel-gyro_comp));
	Drivetrain::GetInstance()->SetRight((cur_vel+gyro_comp));

	//for Testing
	//cout <<"info: set drivetrain to " << cur_vel <<" RPM" << endl;
	//cout <<"info: heading error is " << cur_angle_err << "Degrees" << endl;
	//cout <<"info: gyro_comp " << gyro_comp << "" << endl;
	cout << "info: Left Distance " << act_ldist << endl;
	cout <<"info: Set drivetrain V to" << Drivetrain::GetInstance()->RPMtoIPS(cur_vel) << "IPS" << endl;

	log->AddtoBuffer("act_lvel",Drivetrain::GetInstance()->RPMtoIPS(cur_vel-gyro_comp));
	log->AddtoBuffer("act_rvel",Drivetrain::GetInstance()->RPMtoIPS(cur_vel+gyro_comp));
	log->AddtoBuffer("act_ldist", act_ldist);
	log->AddtoBuffer("act_rdist", act_rdist);
	log->WriteBuffertoFile();

	frc::SmartDashboard::PutNumber("profileV", Drivetrain::GetInstance()->RPMtoIPS(cur_vel));
	frc::SmartDashboard::PutNumber("profileD", cur_dist);
	frc::SmartDashboard::PutNumber("ActualLV", Drivetrain::GetInstance()->RPMtoIPS(Drivetrain::GetInstance()->GetLeftVelocity()));
	frc::SmartDashboard::PutNumber("ActualRV", Drivetrain::GetInstance()->RPMtoIPS(Drivetrain::GetInstance()->GetRightVelocity()));
	frc::SmartDashboard::PutNumber("ActualD", Drivetrain::GetInstance()->GetLeftDistance());
	frc::SmartDashboard::PutNumber("outputLeftV", Drivetrain::GetInstance()->GetLeftThrottle());
	frc::SmartDashboard::PutNumber("outputRightV", Drivetrain::GetInstance()->GetRightThrottle());

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
	log->CloseFile();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {
	End();
}
