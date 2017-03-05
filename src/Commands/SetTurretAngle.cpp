#include "SetTurretAngle.h"
#include "Subsystems/Turret.h"
#include "math.h"

SetTurretAngle::SetTurretAngle(double angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Turret::GetInstance());
	m_input_angle = angle;
	m_init_angle = Turret::GetInstance()->GetBigAngle();
}

// Called just before this Command runs the first time
void SetTurretAngle::Initialize() {
	m_isFinished = false;

	Turret::GetInstance()->ConfigClosedLoop();

}

// Called repeatedly when this Command is scheduled to run
void SetTurretAngle::Execute() {
	float cur_angle = Turret::GetInstance()->GetBigAngle();
	Turret::GetInstance()->SetBigAngle(m_input_angle);
	m_final_angle = cur_angle - m_input_angle;
	if(abs(cur_angle) <= 0.3)
	{
		tolerance_delay++;
		if(tolerance_delay > 5)
			m_isFinished = true;
	}
	else
		tolerance_delay = 0;
}

// Make this return true when this Command no longer needs to run execute()
bool SetTurretAngle::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void SetTurretAngle::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetTurretAngle::Interrupted() {

}
