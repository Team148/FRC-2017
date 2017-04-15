#include "SetRingLight.h"
#include "Subsystems/Shooter.h"

SetRingLight::SetRingLight(bool on) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_on = on;
}

// Called just before this Command runs the first time
void SetRingLight::Initialize() {
	Shooter::GetInstance()->SetRingLightOn(m_on);
}

// Called repeatedly when this Command is scheduled to run
void SetRingLight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SetRingLight::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetRingLight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetRingLight::Interrupted() {
	End();
}
