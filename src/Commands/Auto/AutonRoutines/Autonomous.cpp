#include "Autonomous.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/TurnPID.h"
#include "Commands/Auto/TurnTMP.h"
#include "Commands/Auto/ArcadeDriveTurn.h"


Autonomous::Autonomous(bool red, int getGears, bool isShooting, bool getHopper)
{


//	AddSequential(new ArcadeDriveTurn(-90));
//	//AddSequential(new WaitCommand(0.5));
//	AddSequential(new ArcadeDriveTurn(90));
//	AddSequential(new ArcadeDriveTurn(-45));
//	//AddSequential(new WaitCommand(0.5));
//	AddSequential(new ArcadeDriveTurn(45));

	switch(red)
	{
		RED:
			switch(getGears)
			{

			}
		break;

		BLUE:

		break;
	}


}
