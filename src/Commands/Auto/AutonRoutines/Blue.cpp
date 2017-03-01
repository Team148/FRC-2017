#include "Blue.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/ArcadeDriveTurn.h"
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/SetIntakeArm.h"
#include "Commands/Auto/SetIntake.h"
#include "Commands/SetIntakeBall.h"
#include "Commands/SetIntakeGear.h"
#include "Subsystems/Intake.h"

#include "WPILib.h"



Blue::Blue(int autonSelection) : frc::CommandGroup("Blue")
{
	switch(autonSelection)
	{
	case BOILER_GEAR_: Boiler_GetGear(); break;
	case BOILER_GEAR_HOPPER_SHOOT: Boiler_GetGear_ShootHopper(); break;
	case CENTER_GEAR: Center_GetGear(); break;
	case RETRIEVAL_GEAR: Retrieval_GetGear(); break;
	case RETRIEVAL_TWOGEAR: Retrieval_GetTwoGear(); break;
	}
}


//BOILER SIDE AUTONS
void Blue::Boiler_GetGear()
{
//	AddSequential(new Drive(-92,25));
//	AddSequential(new ArcadeDriveTurn(55));
//	AddSequential(new Drive(-27,15));
//	AddSequential(new Drive(36,15));

	AddSequential(new Drive(-85,25));
	AddSequential(new ArcadeDriveTurn(40));
	AddSequential(new Drive(-27,15));
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
	AddSequential(new Drive(79, 20));
	AddSequential(new SetIntake(0.05));
	AddParallel(new Drive(-45, 30));

//	AddSequential(new Drive(-70,40));
//	AddSequential(new Drive(70,40));
//	AddSequential(new Drive(-210,40));
//	AddSequential(new Drive(210,40));



}
//-------------------------------------

//RETRIEVAL SIDE AUTONS
void Blue::Retrieval_GetGear()
{
	AddSequential(new Drive(-84,25));
	AddSequential(new ArcadeDriveTurn(-40));
	AddSequential(new Drive(-30,15));
	AddSequential(new Drive(36,15));
}
void Blue::Retrieval_GetTwoGear()
{
	AddSequential(new Drive(-84,25));
	AddSequential(new ArcadeDriveTurn(-40));
	AddSequential(new Drive(-30,15));
	AddParallel(new CalibrateArm());
	AddSequential(new Drive(60,25));
	AddSequential(new SetIntake(0.0));
	AddSequential(new ArcadeDriveTurn(40));
	AddSequential(new Drive(42,20));
	if(Intake::GetInstance()->IsBeamBroke())
	{
		AddParallel(new SetIntakeBall(0.0));
		AddParallel(new SetIntakeGear(0.0));
	}
	else
	{
		AddParallel(new SetIntakeBall(1.0));
		AddParallel(new SetIntakeGear(1.0));
	}



}
//-------------------------------------
