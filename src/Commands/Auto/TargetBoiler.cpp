#include "TargetBoiler.h"
#include "Subsystems/Turret.h"

TargetBoiler::TargetBoiler(bool enable) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_enable = enable;
}

// Called just before this Command runs the first time
void TargetBoiler::Initialize() {

}

void TargetBoiler::Execute() {
	Turret::GetInstance()->TargetBoiler(m_enable);
}

// Make this return true when this Command no longer needs to run execute()
bool TargetBoiler::IsFinished() {
	return false;
}

void TargetBoiler::End() {

}

void TargetBoiler::Interrupted() {
	End();
}
