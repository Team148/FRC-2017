#include "StopGearRoll_IntakeUp.h"
#include "Subsystems/Intake.h"

StopGearRoll_IntakeUp::StopGearRoll_IntakeUp() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void StopGearRoll_IntakeUp::Initialize() {
	m_IsFinished = false;
	m_startTime = frc::Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void StopGearRoll_IntakeUp::Execute() {

	Intake::GetInstance()->SetArm(1.2);
	if(frc::Timer::GetFPGATimestamp()-m_startTime >= 0.5)
	{
		Intake::GetInstance()->SetGear(0.0);
		m_IsFinished = true;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool StopGearRoll_IntakeUp::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void StopGearRoll_IntakeUp::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopGearRoll_IntakeUp::Interrupted() {

}
