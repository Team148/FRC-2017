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


	AddSequential(new ArcadeDriveTurn(-90));
	//AddSequential(new WaitCommand(0.5));
	AddSequential(new ArcadeDriveTurn(90));
	AddSequential(new ArcadeDriveTurn(-45));
	//AddSequential(new WaitCommand(0.5));
	AddSequential(new ArcadeDriveTurn(45));
//	AddSequential(new Drive(70,70));
//	AddSequential(new Drive(-70,70));

//	switch(red)
//	{
//		case RED: // CALL RED(NEW asdf123())
//			switch(position)
//			{
//				case POSITION_BOILER:
//					if(getGears == 1 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR));
//					else if(getGears == 2 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_TWO_GEAR));
//					else if(getGears == 1 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_GEAR_HOPPER_SHOOT));
//					else if(getGears == 0 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_HOPPER_SHOOT));
//				break;
//				case POSITION_CENTER:
//					if(getGears == 1 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_GEAR));
//					else if(getGears == 2 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (CENTER_TWO_GEAR));
//				break;
//				case POSITION_RETRIEVAL:
//					if(getGears == 1 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR));
//					else if(getGears == 2 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_TWO_GEAR));
//					else if(getGears == 1 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_GEAR_HOPPER_SHOOT));
//					else if(getGears == 0 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_HOPPER_SHOOT));
//				break;
//			}
//		break;
//
//		case BLUE: // CALL BLUE(NEW asdf123())
//			switch(position)
//			{
//			case POSITION_BOILER:
//				if(getGears == 1 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR));
//				else if(getGears == 2 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_TWO_GEAR));
//				else if(getGears == 1 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_HOPPER_SHOOT));
//				else if(getGears == 0 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_HOPPER_SHOOT));
//			break;
//			case POSITION_CENTER:
//				if(getGears == 1 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_GEAR));
//				else if(getGears == 2 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_TWO_GEAR));
//			break;
//			case POSITION_RETRIEVAL:
//				if(getGears == 1 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR));
//				else if(getGears == 2 && !isShooting && !getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_TWO_GEAR));
//				else if(getGears == 1 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_HOPPER_SHOOT));
//				else if(getGears == 0 && isShooting && getHopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_HOPPER_SHOOT));
//			break;
//			}
//		break;
//	}


}
