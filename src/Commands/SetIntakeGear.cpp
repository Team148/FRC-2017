#include "SetIntakeGear.h"

SetIntakeGear::SetIntakeGear(float speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());

	m_speed = speed;
}

// Called once when the command executes
void SetIntakeGear::Initialize() {
	Intake::GetInstance()->SetGear(m_speed);

}
