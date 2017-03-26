#include "FeedShooter.h"
#include "Subsystems/Conveyor.h"

#include "Constants.h"

FeedShooter::FeedShooter(bool on) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Conveyor::GetInstance());
	m_on = on;
}

// Called once when the command executes
void FeedShooter::Initialize()
{
	if(m_on)
	{
		Conveyor::GetInstance()->SetAgitator(CONVEYER_AGITATOR_VOLTAGE);
		Conveyor::GetInstance()->SetKicker(CONVEYER_KICKER_VOLTAGE);
	}
	else
	{
		Conveyor::GetInstance()->SetAgitator(0.0);
		Conveyor::GetInstance()->SetKicker(0.0);
	}
}
