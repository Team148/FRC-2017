#include "Blue.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/ArcadeDriveTurn.h"
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/SetIntakeArm.h"
#include "Commands/Auto/SetIntake.h"
#include "WPILib.h"



Blue::Blue(int autonSelection) : frc::CommandGroup("Blue")
{
	switch(autonSelection)
	{
	case BOILER_GEAR_: Boiler_GetGear(); break;
	case BOILER_GEAR_HOPPER_SHOOT: Boiler_GetGear_ShootHopper(); break;
	case CENTER_GEAR: Center_GetGear(); break;
	case RETRIEVAL_GEAR: Retrieval_GetGear(); break;
	}
}


//BOILER SIDE AUTONS
void Blue::Boiler_GetGear()
{
	AddSequential(new Drive(-42,25));
	AddSequential(new ArcadeDriveTurn(53));
	AddSequential(new Drive(-25,15));
	AddSequential(new Drive(36,15));



}
void Blue::Boiler_GetGear_ShootHopper()
{
	AddSequential(new Drive(69,-25));
	AddSequential(new ArcadeDriveTurn(45));
	AddSequential(new Drive(36,-25));
	AddSequential(new Drive(36,25));
	AddSequential(new ArcadeDriveTurn(45));
	AddSequential(new Drive(69,25));

}
//-------------------------------------

//CENTER POSITION AUTONS
void Blue::Center_GetGear()
{
	AddParallel(new CalibrateArm());
	AddSequential(new Drive(80, 20));
	//AddSequential(new SetIntakeArm(0,2));
	AddSequential(new SetIntake(0.05));
	AddParallel(new Drive(45, 30));
//	AddSequential(new Drive(-69,25));
//	AddSequential(new Drive(36,25));


}
//-------------------------------------

//RETRIEVAL SIDE AUTONS
void Blue::Retrieval_GetGear()
{
	AddSequential(new Drive(-42,25));
	AddSequential(new ArcadeDriveTurn(-53));
	AddSequential(new Drive(-25,15));
	AddSequential(new Drive(36,15));
}
//-------------------------------------
