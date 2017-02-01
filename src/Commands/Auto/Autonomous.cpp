#include "Autonomous.h"

#include <iostream>

#include "Drive.h"


Autonomous::Autonomous() :
		frc::CommandGroup("Autonomous") {
	AddSequential(new Drive(240,100));
	AddSequential(new Drive(120,50));
	AddSequential(new Drive(100,100));

}
