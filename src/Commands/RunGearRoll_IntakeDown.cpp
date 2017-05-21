#include "RunGearRoll_IntakeDown.h"
#include "Subsystems/Intake.h"

RunGearRoll_IntakeDown::RunGearRoll_IntakeDown() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void RunGearRoll_IntakeDown::Initialize() {
	m_IsFinished = false;

}

// Called repeatedly when this Command is scheduled to run
void RunGearRoll_IntakeDown::Execute()
{
	Intake::GetInstance()->SetArm(INTAKE_ARM_POSITION_DOWN);
	Intake::GetInstance()->SetGear(1.0);
	m_IsFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool RunGearRoll_IntakeDown::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void RunGearRoll_IntakeDown::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunGearRoll_IntakeDown::Interrupted() {

}
