#include "turretLocking.h"
#include "Subsystems/Turret.h"

turretLocking::turretLocking(bool lock) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Turret::GetInstance());
	m_lock = lock;
}

// Called once when the command executes
void turretLocking::Initialize()
{
	m_IsFinished = false;
}
void turretLocking::Execute()
{
	Turret::GetInstance()->lockTurretAngle(m_lock);
}
bool turretLocking::IsFinished()
{
	return m_IsFinished;
}
void turretLocking::End()
{

}
void turretLocking::Interrupted()
{

}
