#include "SetIntake.h"
#include "Subsystems/Intake.h"

SetIntake::SetIntake(float angle) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Intake::GetInstance());
	m_angle = angle;
}

// Called once when the command executes
void SetIntake::Initialize() {
	if(Intake::GetInstance()->IsClosedLoop()) {
		Intake::GetInstance()->SetArmAngle(m_angle);
	}
}
