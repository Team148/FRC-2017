#include "Autonomous.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/TurnPID.h"
#include "Commands/Auto/TurnTMP.h"
#include "Commands/Auto/ArcadeDriveTurn.h"
#include "Commands/Auto/AutonRoutines/Red.h"
#include "Commands/Auto/AutonRoutines/Blue.h"
#include "Constants.h"


Autonomous::Autonomous(bool red, int position, int getGears, bool isShooting, bool getHopper)
{


//	AddSequential(new ArcadeDriveTurn(-90));
//	//AddSequential(new WaitCommand(0.5));
//	AddSequential(new ArcadeDriveTurn(90));
//	AddSequential(new ArcadeDriveTurn(-45));
//	//AddSequential(new WaitCommand(0.5));
//	AddSequential(new ArcadeDriveTurn(45));

	switch(red)
	{
		case RED:
			switch(position)
			{
				case POSITION_BOILER:
					if(getGears && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR));
					if(getGears && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_GEAR_HOPPER_SHOOT));

				break;
				case POSITION_CENTER:
				break;
				case POSITION_RETRIEVAL:
				break;
			}
		break;

		case BLUE:
			switch(position)
			{
				case POSITION_BOILER:
				break;
				case POSITION_CENTER:
				break;
				case POSITION_RETRIEVAL:
				break;
			}
		break;
	}


}
