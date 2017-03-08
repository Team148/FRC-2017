#include "Blue.h"

#include <iostream>

#include "Commands/Auto/Drive.h"
#include "Commands/Auto/ArcadeDriveTurn.h"
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/SetIntakeArm.h"
#include "Commands/Auto/SetIntake.h"
#include "Commands/SetIntakeBall.h"
#include "Commands/SetIntakeGear.h"
#include "Commands/Auto/SetBallGearUntilBeam.h"
#include "Commands/SetTurretAngle.h"
#include "Commands/Auto/SetAgitator.h"
#include "Commands/Auto/SetKicker.h"
#include "Commands/Auto/SetShooterSpeed.h"
#include "Subsystems/Intake.h"
#include "Commands/AutoGearScore.h"
#include "Constants.h"

#include "WPILib.h"



Blue::Blue(int autonSelection) : frc::CommandGroup("Blue")
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
void Blue::Boiler_GetGear()
{
//	AddSequential(new Drive(-92,25));
//	AddSequential(new ArcadeDriveTurn(55));
//	AddSequential(new Drive(-27,15));
//	AddSequential(new Drive(36,15));

	AddSequential(new Drive(-85,30));
	AddSequential(new ArcadeDriveTurn(48));
	AddSequential(new Drive(-34,20));
	AddSequential(new Drive(43,20));


}
void Blue::Boiler_GetTwoGear()
{


}
void Blue::Boiler_GetGear_ShootHopper()
{
	AddSequential(new Drive(-85,30));
	AddSequential(new ArcadeDriveTurn(48));
	AddSequential(new Drive(-34,20));
	AddParallel(new CalibrateArm());
	AddSequential(new Drive(43,20));

	AddParallel(new SetIntake(0.0));
	AddSequential(new ArcadeDriveTurn(72));
	AddSequential(new Drive(60,30));
	AddSequential(new ArcadeDriveTurn(-35));
	AddParallel(new SetTurretAngle(90.0));
	AddParallel(new SetShooterSpeed(SHOOTER_SET_POINT_A));
	AddParallel(new SetAgitator(true, 10.0));
	AddParallel(new SetKicker(true, 10.0));
	AddSequential(new Drive(15,30));


//	AddSequential(new ArcadeDriveTurn(90));
//	AddSequential(new ArcadeDriveTurn(-90));
//	AddSequential(new ArcadeDriveTurn(45));
//	AddSequential(new ArcadeDriveTurn(-45));

}
void Blue::Boiler_ShootHopper()
{

}
//-------------------------------------

//CENTER POSITION AUTONS
void Blue::Center_GetGear()
{
	 // replace with auto gear score eventually pls
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
void Blue::Retrieval_GetGear()
{
	AddSequential(new Drive(-85,30));
	AddSequential(new ArcadeDriveTurn(-48));
	AddSequential(new Drive(-34,20));
	AddSequential(new Drive(43,20));
}
void Blue::Retrieval_GetTwoGear()
{
	AddSequential(new Drive(-94,70)); // v 40
	AddSequential(new ArcadeDriveTurn(-48));
	AddSequential(new Drive(-32,40));// v 20
	// scored 1st gear

	AddParallel(new CalibrateArm());
	AddSequential(new Drive(60,60)); // v40
	AddSequential(new SetIntake(0.0));
	AddSequential(new ArcadeDriveTurn(50));
	AddParallel(new SetIntakeGear(1.0));
	AddSequential(new Drive(70,70)); // v50
	AddParallel(new SetIntakeGear(0.0));
	AddSequential(new Drive(-71,70)); // v50

	// got 2nd gear
	AddParallel(new SetIntakeGear(0.0));
	//AddParallel(new SetIntakeBall(0.0));
	//AddParallel(new SetIntakeGear(0.0));
	//AddSequential(new Drive(-35,35));
	AddParallel(new SetIntake(1.15));
	AddSequential(new ArcadeDriveTurn(115));
	//AddSequential(new Drive(30,30));


	AddSequential(new Drive(67,30));
	AddParallel(new SetIntakeBall(-0.1));
	AddSequential(new SetIntake(INTAKE_ARM_POSITION_UP*0.55));
	AddSequential(new Drive(-20, 30));







}
//-------------------------------------
