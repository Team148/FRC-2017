#include "SetAgitator.h"
#include "Subsystems/Conveyor.h"

SetAgitator::SetAgitator(bool on, double timeout) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Conveyor::GetInstance());
	m_on = on;
	m_timeout = timeout;
}

// Called just before this Command runs the first time
void SetAgitator::Initialize() {
	if(!m_timeout == 0.0)
	{
		SetTimeout(m_timeout);
	}
	m_IsFinished = false;

}

// Called repeatedly when this Command is scheduled to run
void SetAgitator::Execute() {
	if(m_on)
	{
		Conveyor::GetInstance()->SetAgitator(-CONVEYER_AGITATOR_VOLTAGE);
	}
	else
	{
		Conveyor::GetInstance()->SetAgitator(0.0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool SetAgitator::IsFinished() {
	return m_IsFinished || IsTimedOut();
}

// Called once after isFinished returns true
void SetAgitator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetAgitator::Interrupted() {

}
