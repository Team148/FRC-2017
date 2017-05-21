#include "SetIntakeBall.h"

SetIntakeBall::SetIntakeBall(float speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
	m_speed = speed;
}

// Called once when the command executes
void SetIntakeBall::Initialize() {
	Intake::GetInstance()->SetBall(m_speed);
}
