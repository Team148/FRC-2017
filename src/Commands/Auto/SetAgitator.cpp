#include "SetAgitator.h"
#include "Subsystems/Conveyor.h"

SetAgitator::SetAgitator(bool on) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Conveyor::GetInstance());
	m_on = on;
}

// Called just before this Command runs the first time
void SetAgitator::Initialize() {
	if(m_on)
	{
		Conveyor::GetInstance()->SetAgitator(-CONVEYER_AGITATOR_VOLTAGE);
	}
	else
	{
		Conveyor::GetInstance()->SetAgitator(0.0);
	}


}

// Called repeatedly when this Command is scheduled to run
void SetAgitator::Execute() {
	m_IsFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetAgitator::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetAgitator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetAgitator::Interrupted() {

}
