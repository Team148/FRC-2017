#include "SetKicker.h"
#include "Subsystems/Conveyor.h"

SetKicker::SetKicker(bool on) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Conveyor::GetInstance());
	m_on = on;
}

// Called just before this Command runs the first time
void SetKicker::Initialize() {

	if(m_on)
	{
		Conveyor::GetInstance()->SetKicker(CONVEYER_KICKER_VOLTAGE);
	}
	else
	{
		Conveyor::GetInstance()->SetKicker(0.0);
	}
}

// Called repeatedly when this Command is scheduled to run
void SetKicker::Execute() {
	m_IsFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetKicker::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void SetKicker::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetKicker::Interrupted() {

}
