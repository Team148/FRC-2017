#include "TargetBoiler.h"
#include "Subsystems/Turret.h"
#include "Subsystems/Shooter.h"

TargetBoiler::TargetBoiler(bool enable) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
//	m_enable = enable;
	Requires(Turret::GetInstance());
	Requires(Shooter::GetInstance());
	m_enable = enable;
}

// Called just before this Command runs the first time
void TargetBoiler::Initialize() {
	m_expiration = 0;
}

void TargetBoiler::Execute() {
	if (Turret::GetInstance()->IsTargetValid())
	{
		Turret::GetInstance()->TargetBoiler(m_enable);
		Shooter::GetInstance()->SetRPM(Turret::GetInstance()->GetVisionShooterRPM());
	}
	else
		m_expiration++;
}

// Make this return true when this Command no longer needs to run execute()
bool TargetBoiler::IsFinished() {
	if(m_expiration>70)
		return true;
	else
		return false;
}

void TargetBoiler::End() {
	Turret::GetInstance()->TargetBoiler(false);
}

void TargetBoiler::Interrupted() {
	End();
}
