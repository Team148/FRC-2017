#include "ConfigureIntake.h"
#include "Subsystems/Intake.h"

ConfigureIntake::ConfigureIntake() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called once when the command executes
void ConfigureIntake::Initialize() {
	if(!Intake::GetInstance()->IsClosedLoop())
	{
		if(Intake::GetInstance()->isSensorPluggedIn() == 1) Intake::GetInstance()->ConfigureClosedLoop();
		else
		{
			Intake::GetInstance()->ConfigureOpenLoop();
		}
	}
}
