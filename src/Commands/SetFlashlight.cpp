#include "SetFlashlight.h"
#include "Subsystems/Shooter.h"

SetFlashlight::SetFlashlight(bool set) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Shooter::GetInstance());
	m_set = set;
}

// Called once when the command executes
void SetFlashlight::Initialize() {

	Shooter::GetInstance()->SetFlashlightOn(m_set);
}
