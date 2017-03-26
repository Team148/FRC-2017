#include "turretLocking.h"
#include "Subsystems/Turret.h"

turretLocking::turretLocking(bool lock) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Turret::GetInstance());
	m_lock = lock;
}

// Called once when the command executes
void turretLocking::Initialize() {
	Turret::GetInstance()->lockTurretAngle(m_lock);
}
