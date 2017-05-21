#include "SetTurretAngleDelta.h"
#include "Subsystems/Turret.h"
#include "math.h"

SetTurretAngleDelta::SetTurretAngleDelta(double angle_delta, bool delay) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Turret::GetInstance());
	m_init_angle = Turret::GetInstance()->GetBigAngle();
	m_target_angle = angle_delta + m_init_angle;
	m_delay = delay;
}

// Called just before this Command runs the first time
void SetTurretAngleDelta::Initialize() {
	m_isFinished = false;

	Turret::GetInstance()->ConfigClosedLoop();

}

// Called repeatedly when this Command is scheduled to run
void SetTurretAngleDelta::Execute() {
	float cur_angle = Turret::GetInstance()->GetBigAngle();
	Turret::GetInstance()->SetBigAngle(m_target_angle);
	m_angle_error = cur_angle - m_target_angle;
	if(abs(m_angle_error) <= 0.3)
	{
		tolerance_delay++;
		if(tolerance_delay > 5)
			m_isFinished = true;
	}
	else
		tolerance_delay = 0;
	if(!m_delay)
		m_isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetTurretAngleDelta::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void SetTurretAngleDelta::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetTurretAngleDelta::Interrupted() {

}
