#include "TurnTMP.h"

TurnTMP::TurnTMP(float degrees) {
	Requires(Drivetrain::GetInstance());
	m_deg_input = degrees;
}

// Called just before this Command runs the first time
void TurnTMP::Initialize() {
	//reset isFinished
	m_isFinished=0;

	//check that the Drivetrain is in closed loop
	if(!Drivetrain::GetInstance()->isClosedLoop())
		Drivetrain::GetInstance()->configClosedLoop();

	//check where we pointing
	m_initangle = Drivetrain::GetInstance()->GetAngle();

	//calculate the final destination angle
	m_finalangle = m_initangle+m_deg_input;

	//convert to radians
	m_rad_distance = (M_PI/180) * m_deg_input;

	//ensure queue is empty
	while(!m_output.empty())
		m_output.pop();


	//generate profile
	//to begin, check if a triangle or trapezoid profile is needed.
	float accel_dist = 0.5*m_cruiseVelocity*m_cruiseVelocity/m_maxAccelRate;

	if(accel_dist*2 > m_rad_distance) {
		//we will never reach the requested speed, so a triangle profile is generated
		cout << "info: generating Triangle profile" << endl;
		int accel_segments = ceil(m_cruiseVelocity/m_maxAccelRate/m_dt);

		//generate acceleration curve
		for(int i = 0;i <= accel_segments;i++) {
			double t = m_dt*i;
		    m_output.push(m_maxAccelRate*t);
		 }
		float top_speed_reached = m_output.back();

		//generate deceleration curve
		for(int i=0 ;i < accel_segments;i++) {
			float t = m_dt*i;
		    // v = u + at
		    float velocity = top_speed_reached+(-m_maxAccelRate*t);
		    if(velocity > 0)
		    	m_output.push(velocity);
		 }
		 //push last point
		 m_output.push(0);

		cout << "info: generated a profile with "<< accel_segments*2 <<" Points. time: " << accel_segments*2*m_dt << "sec"<< endl;
	}
	else {
		//generate a trapezoid profile
		cout << "info: generating Trapezoid Profile" << endl;

		float hold_distance = m_rad_distance - (accel_dist * 2);
		float hold_time = hold_distance/m_cruiseVelocity;

		int accel_segments = ceil(m_cruiseVelocity / m_maxAccelRate / m_dt);
		int hold_segments = hold_time / m_dt;

		//generate acceleration curve
		for(int i = 0;i <= accel_segments;i++) {
			float t = m_dt*i;
			float accvelocity = m_maxAccelRate*t;
			if(accvelocity > m_cruiseVelocity)
				m_output.push(m_cruiseVelocity);
			else
				m_output.push(accvelocity);
		}

		//generate the hold
		for(int y = 0;y < hold_segments;y++) {
			m_output.push(m_cruiseVelocity);
		}

		//generate deceleration curve
		for(int i=0 ;i < accel_segments;i++) {
			float t = m_dt*i;
			float decvelocity = m_cruiseVelocity+(-m_maxAccelRate*t);

			//check for undershoot
			if(decvelocity < 0)
				m_output.push(0);
			else
				m_output.push(decvelocity);

		}
		//push last point
		m_output.push(0);


		cout<<"info: generated profile with"<< accel_segments*2+hold_segments << " Points. time: " << accel_segments*2*m_dt+hold_time <<"sec"<< endl;
	}
}

// Called repeatedly when this Command is scheduled to run
void TurnTMP::Execute() {

	float cur_vel = m_output.front();

	//after setting, remove from queue
	m_output.pop();

	//convert IPS to RPM
	cur_vel = Drivetrain::GetInstance()->IPStoRPM(cur_vel);

	//SetLeft and SetRight to current queue
	Drivetrain::GetInstance()->SetLeft(cur_vel);
	Drivetrain::GetInstance()->SetRight(-cur_vel);

	//once the queue is empty, set isFinished
	if(m_output.empty())
		m_isFinished=true;
}


// Make this return true when this Command no longer needs to run execute()
bool TurnTMP::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void TurnTMP::End() {
	Drivetrain::GetInstance()->SetLeft(0);
	Drivetrain::GetInstance()->SetRight(0);
	cout <<"info: set drivetrain to " << 0 <<" RPM" << endl;

	//empty the queue if interrupted
	while(!m_output.empty())
		m_output.pop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnTMP::Interrupted() {
	End();
}
