#include "Red.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/ArcadeDriveTurn.h"
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/SetIntakeArm.h"
#include "Commands/Auto/SetIntake.h"
#include "Commands/SetIntakeBall.h"
#include "Commands/SetIntakeGear.h"
#include "Commands/Auto/SetBallGearUntilBeam.h"
#include "Subsystems/Intake.h"
#include "Constants.h"

#include "WPILib.h"



Red::Red(int autonSelection) : frc::CommandGroup("Red")
{
	switch(autonSelection)
	{
	case BOILER_GEAR: Boiler_GetGear(); break;
	case BOILER_GEAR_HOPPER_SHOOT: Boiler_GetGear_ShootHopper(); break;
	case BOILER_HOPPER_SHOOT: Boiler_ShootHopper(); break;
	case BOILER_TWO_GEAR: Boiler_GetTwoGear(); break;

	case CENTER_GEAR: Center_GetGear(); break;

	case RETRIEVAL_GEAR: Retrieval_GetGear(); break;
	case RETRIEVAL_TWOGEAR: Retrieval_GetTwoGear(); break;
	}
}


//BOILER SIDE AUTONS
void Red::Boiler_GetGear()
{
//	AddSequential(new Drive(-92,25));
//	AddSequential(new ArcadeDriveTurn(55));
//	AddSequential(new Drive(-27,15));
//	AddSequential(new Drive(36,15));

	AddSequential(new Drive(-94,30));
	AddSequential(new ArcadeDriveTurn(-51));
	AddSequential(new Drive(-34,20));
	AddSequential(new Drive(43,20));


}
void Red::Boiler_GetTwoGear()
{

}
void Red::Boiler_GetGear_ShootHopper()
{
	AddSequential(new Drive(69,-25));
	AddSequential(new ArcadeDriveTurn(45));
	AddSequential(new Drive(36,-25));
	AddSequential(new Drive(36,25));
	AddSequential(new ArcadeDriveTurn(45));
	AddSequential(new Drive(69,25));

}
void Red::Boiler_ShootHopper()
{

}
//-------------------------------------

//CENTER POSITION AUTONS
void Red::Center_GetGear()
{
	AddParallel(new CalibrateArm());
	AddSequential(new Drive(79, 20));
	AddParallel(new SetIntakeBall(-0.1));
	AddSequential(new SetIntake(INTAKE_ARM_POSITION_UP*0.55));
	AddSequential(new Drive(-20, 25));

//	AddSequential(new Drive(-70,40));
//	AddSequential(new Drive(70,40));
//	AddSequential(new Drive(-210,40));
//	AddSequential(new Drive(210,40));



}
//-------------------------------------

//RETRIEVAL SIDE AUTONS
void Red::Retrieval_GetGear()
{
	AddSequential(new Drive(-91,30));
	AddSequential(new ArcadeDriveTurn(49));
	AddSequential(new Drive(-34,20));
	AddSequential(new Drive(43,20));
}
void Red::Retrieval_GetTwoGear()
{
	AddSequential(new Drive(-84,25));
	AddSequential(new ArcadeDriveTurn(-40));
	AddSequential(new Drive(-30,15));
	AddParallel(new CalibrateArm());
	AddSequential(new Drive(60,25));
	AddSequential(new SetIntake(0.0));
	AddSequential(new ArcadeDriveTurn(40));
	AddParallel(new SetBallGearUntilBeam());
	AddSequential(new Drive(26,22));
	AddSequential(new Drive(-28,18));
	AddParallel(new SetIntake(INTAKE_ARM_POSITION_UP));







}
//-------------------------------------
