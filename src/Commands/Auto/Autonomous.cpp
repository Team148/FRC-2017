#include "Autonomous.h"

#include <iostream>

#include "Drive.h"
#include "TurnPID.h"
#include "TurnTMP.h"


Autonomous::Autonomous() :
		frc::CommandGroup("Autonomous") {
	AddSequential(new Drive(70,100));
	AddSequential(new TurnPID(90));
	//AddSequential(new TurnTMP(90,60));

}
