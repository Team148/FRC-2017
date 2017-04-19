#include "Autonomous.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/TurnPID.h"
#include "Commands/Auto/TurnTMP.h"
#include "Commands/Auto/ArcadeDriveTurn.h"
#include "Commands/Auto/AutonRoutines/Red.h"
#include "Commands/Auto/AutonRoutines/Blue.h"
#include "Commands/SetTurretAngle.h"
#include "Commands/Auto/SetRingLight.h"
#include "Commands/Auto/TargetBoiler.h"
#include "Commands/Auto/SetShooterSpeed.h"
#include "Commands/FeedShooter.h"
#include "Commands/ConfigureIntake.h"
#include "Constants.h"


Autonomous::Autonomous(bool red, int position, int getGears, bool isShooting, bool getHopper)
{
//	AddSequential(new Drive(100,150));
//	AddSequential(new WaitCommand(5.0));
//	AddSequential(new Drive(-100,150));
//	AddParallel(new SetShooterSpeed(SHOOTER_SET_POINT_A));
//	AddSequential(new WaitCommand(5.0));
//	AddSequential(new SetRingLight(true));
//	AddSequential(new SetTurretAngle(83));
//	AddParallel(new TargetBoiler(true));
//	AddSequential(new WaitCommand(2.0));
//	AddSequential(new FeedShooter(true));


		AddSequential(new ConfigureIntake());
		AddParallel(new SetShooterSpeed(SHOOTER_SET_POINT_A), true);

		AddParallel(new SetTurretAngle(-90));
		AddSequential(new Drive(-76, 150));
		AddSequential(new ArcadeDriveTurn(-85));
		AddSequential(new Drive(-45, 150));
		AddSequential(new SetRingLight(true));
		AddParallel(new TargetBoiler(true));
		AddSequential(new WaitCommand(0.5));
		AddParallel(new FeedShooter(true));



//




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
