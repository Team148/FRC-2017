#include "SetKicker.h"
#include "Subsystems/Conveyor.h"

SetKicker::SetKicker(bool on, double timeout) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Conveyor::GetInstance());
	m_on = on;
	m_timeout = timeout;
}

// Called just before this Command runs the first time
void SetKicker::Initialize() {
	m_IsFinished = false;
	if(!m_timeout == 0.0)
	{
		SetTimeout(m_timeout);
	}



}

// Called repeatedly when this Command is scheduled to run
void SetKicker::Execute() {
	if(m_on)
	{
		Conveyor::GetInstance()->SetKicker(CONVEYER_KICKER_VOLTAGE);
	}
	else
	{
		Conveyor::GetInstance()->SetKicker(0.0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool SetKicker::IsFinished() {
	return m_IsFinished || IsTimedOut();
}

// Called once after isFinished returns true
void SetKicker::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetKicker::Interrupted() {

}
