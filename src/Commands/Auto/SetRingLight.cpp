#include "SetRingLight.h"
#include "Subsystems/Shooter.h"

SetRingLight::SetRingLight(bool on) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Shooter::GetInstance());
	m_on = on;
}

// Called just before this Command runs the first time
void SetRingLight::Initialize() {
	m_isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SetRingLight::Execute() {
	Shooter::GetInstance()->SetRingLightOn(m_on);
	m_isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetRingLight::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void SetRingLight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetRingLight::Interrupted() {
	End();
}
