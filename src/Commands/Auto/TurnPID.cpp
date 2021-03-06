#include "TurnPID.h"

TurnPID::TurnPID(float degrees) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Drivetrain::GetInstance());
	m_setpoint = degrees;
	//m_controller = new PIDController();

}

// Called just before this Command runs the first time
void TurnPID::Initialize() {
	//reset isFinished
	m_isFinished = 0;

	//Set Drivetrain to OpenLoop
	Drivetrain::GetInstance()->configOpenLoop();

	m_initalAngle = Drivetrain::GetInstance()->GetAngle();
	m_setpoint += m_initalAngle;
}

// Called repeatedly when this Command is scheduled to run
void TurnPID::Execute() {

	//read current angle
	float current_angle = Drivetrain::GetInstance()->GetAngle();

	//calculate output
	float curr_err = m_setpoint - current_angle;
	m_i_err+=curr_err;
	float d_err = curr_err - prev_err;
	float output = m_Kp * curr_err + m_Ki*m_i_err;



	//SetLeft and SetRight
	Drivetrain::GetInstance()->SetLeft(output);
	Drivetrain::GetInstance()->SetRight(-output);

	prev_err = curr_err;

	//check if we're finished
	if(abs(curr_err)<=DRIVE_TURN_TOLERANCE)
		m_isFinished=true;
}

// Make this return true when this Command no longer needs to run execute()
bool TurnPID::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void TurnPID::End() {
	Drivetrain::GetInstance()->SetLeft(0);
	Drivetrain::GetInstance()->SetRight(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnPID::Interrupted() {
	End();
}
