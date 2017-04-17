#include "AutoAim.h"



AutoAim::AutoAim() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
//	Requires(Turret::GetInstance());
}

// Called just before this Command runs the first time
void AutoAim::Initialize() {
	Turret::GetInstance()->UpdateVisionTarget();
	m_yaw_offset = Turret::GetInstance()->GetYawOffset();
	m_yaw_final = Turret::GetInstance()->GetBigAngle() + m_yaw_offset;
	Turret::GetInstance()->SetBigAngle(m_yaw_final);
}

// Called repeatedly when this Command is scheduled to run
void AutoAim::Execute() {
	float error = Turret::GetInstance()->GetBigAngle() - m_yaw_final;

	if(abs(error < 0.5))
		m_isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoAim::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void AutoAim::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoAim::Interrupted() {

}
