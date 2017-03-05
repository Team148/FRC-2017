#include "SetShooterSpeed.h"
#include "Subsystems/Shooter.h"

SetShooterSpeed::SetShooterSpeed(int rpm) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Shooter::GetInstance());
	m_rpm = rpm;
}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize() {
	Shooter::GetInstance()->SetRPM(m_rpm);

}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute() {
	m_IsFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void SetShooterSpeed::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterSpeed::Interrupted() {

}
