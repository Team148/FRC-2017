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
#include "Commands/StopGearRoll_IntakeUp.h"
#include "Commands/RunGearRoll_IntakeDown.h"
#include <Commands/Auto/IntakeAutoGearScore.h>
#include <Commands/AutoGearScoreSub.h>
#include <Commands/turretLocking.h>
#include <Commands/ConfigureIntake.h>

#include "Commands/FeedShooter.h"
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
	case BOILER_GEAR_SHOOT:Boiler_GetGear_Shoot(); break;

	case CENTER_GEAR: Center_GetGear(); break;
	case CENTER_TWO_GEAR: Center_GetTwoGear(); break;
	case CENTER_TWO_GEAR_NOSCORE: Center_GetTwoGear_Noscore(); break;
	case CENTER_TWO_GEAR_NOSCORE_SHOOT: Center_GetTwoGear_Noscore_Shoot(); break;
	case CENTER_GEAR_SHOOT: Center_GetGear_Shoot(); break;

	case RETRIEVAL_GEAR: Retrieval_GetGear(); break;
	case RETRIEVAL_TWOGEAR: Retrieval_GetTwoGear(); break;
	case RETRIEVAL_GEAR_SHOOT: Retrieval_GetGear_Shoot(); break;
	}
}


//BOILER SIDE AUTONS
void Blue::Boiler_GetGear()
{
//	AddSequential(new Drive(-92,25));
//	AddSequential(new ArcadeDriveTurn(55));
//	AddSequential(new Drive(-27,15));
//	AddSequential(new Drive(36,15));

	AddSequential(new ConfigureIntake());
	AddSequential(new Drive(82,120));
	AddSequential(new ArcadeDriveTurn(55));
	AddSequential(new Drive(34,40));
	AddParallel(new IntakeAutoGearScore());
	AddSequential(new Drive(-33,40));


}
void Blue::Boiler_GetTwoGear()
{
	AddSequential(new Drive(100,150));
	AddSequential(new WaitCommand(2.0));
	AddSequential(new Drive(-100,150));
}
void Blue::Boiler_GetGear_ShootHopper()
{
	AddSequential(new Drive(-85,30));
	AddSequential(new ArcadeDriveTurn(48));
	AddSequential(new Drive(-34,20));
	AddParallel(new CalibrateArm(false));
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
	AddSequential(new ConfigureIntake());

	AddParallel(new SetShooterSpeed(6550));
	AddSequential(new WaitCommand(1.5));

	AddParallel(new SetTurretAngle(-84));
	AddSequential(new Drive(-115, 150));
	AddSequential(new ArcadeDriveTurn(-80));
	AddSequential(new Drive(-25, 150));
	AddParallel(new FeedShooter(true));
}
void Blue::Boiler_GetGear_Shoot()
{
	AddParallel(new SetShooterSpeed(6500));
	AddParallel(new SetTurretAngle(41));
	AddSequential(new Drive(82,120));
	AddSequential(new WaitCommand(2.0));
	AddSequential(new FeedShooter(true));
	AddSequential(new WaitCommand(2.0));
	AddSequential(new FeedShooter(false));
	AddParallel(new SetShooterSpeed(0));
	AddSequential(new ArcadeDriveTurn(55));
	AddSequential(new Drive(34,40));
	AddParallel(new IntakeAutoGearScore());
	AddSequential(new Drive(-33,40));

}
//-------------------------------------

//CENTER POSITION AUTONS
void Blue::Center_GetGear()
{
	AddSequential(new ConfigureIntake());
	AddSequential(new Drive(80, 75));
	AddParallel(new IntakeAutoGearScore());
	AddSequential(new Drive(-40,75));

//	AddSequential(new Drive(-70,40));
//	AddSequential(new Drive(70,40));
//	AddSequential(new Drive(-210,40));
//	AddSequential(new Drive(210,40));



}
void Blue::Center_GetGear_Shoot()
{
	AddParallel(new SetShooterSpeed(SHOOTER_SET_POINT_B));
	AddParallel(new SetTurretAngle(88));
	AddSequential(new WaitCommand(4.0));
	AddSequential(new FeedShooter(true));
	AddSequential(new WaitCommand(3.0));
	AddSequential(new FeedShooter(false));
	AddParallel(new SetShooterSpeed(0.0));
	AddParallel(new SetTurretAngle(0.0));
	Center_GetGear();
}
void Blue::Center_GetTwoGear()
{

	//not jank use intake to score all gears
		AddSequential(new ConfigureIntake());
		AddSequential(new Drive(88, 150));
		AddParallel(new IntakeAutoGearScore());
		AddSequential(new Drive(-70, 150));

		AddParallel(new SetIntake(INTAKE_ARM_POSITION_DOWN));
		AddSequential(new ArcadeDriveTurn(100));
		AddParallel(new SetIntakeGear(1.0));
		AddSequential(new Drive(25, 150));
		AddParallel(new StopGearRoll_IntakeUp());
		AddSequential(new Drive(-22.5, 150));
		AddSequential(new ArcadeDriveTurn(-100));

		AddSequential(new Drive(77, 150));
		AddParallel(new IntakeAutoGearScore());
		AddSequential(new Drive(-70, 150));


}
void Blue::Center_GetTwoGear_Noscore()
{
 //not jank use intake to score all gears
	AddSequential(new ConfigureIntake());
	AddSequential(new Drive(80, 150)); //  88
//	AddParallel(new SetIntakeBall(-0.1));
	AddParallel(new IntakeAutoGearScore()); //AddSequential(new SetIntake(INTAKE_ARM_GEAR_POSITION));
	//AddSequential(new Drive(-20, 40));
	AddSequential(new Drive(-65, 150));

	AddParallel(new SetIntake(INTAKE_ARM_POSITION_DOWN));

	AddSequential(new ArcadeDriveTurn(100));
	AddParallel(new SetIntakeGear(1.0));
	AddSequential(new Drive(25, 150));
	AddParallel(new StopGearRoll_IntakeUp());

	AddSequential(new Drive(-22.5, 150));


//	AddSequential(new ArcadeDriveTurn(-100));
//
//	AddSequential(new Drive(77, 150));
//	AddSequential(new SetIntake(INTAKE_ARM_GEAR_POSITION));
//	AddSequential(new Drive(-70, 150));




}
void Blue::Center_GetTwoGear_Noscore_Shoot()
{
	AddParallel(new SetShooterSpeed(SHOOTER_SET_POINT_B));
	AddParallel(new SetTurretAngle(88));
	AddSequential(new WaitCommand(4.0));
	AddSequential(new FeedShooter(true));
	AddSequential(new WaitCommand(3.0));
	AddSequential(new FeedShooter(false));
	AddParallel(new SetShooterSpeed(0.0));
	AddParallel(new SetTurretAngle(0.0));
	Center_GetTwoGear_Noscore();
}
//-------------------------------------

//RETRIEVAL SIDE AUTONS
void Blue::Retrieval_GetGear()
{
	AddSequential(new ConfigureIntake());
	AddSequential(new Drive(83,120));
	AddSequential(new ArcadeDriveTurn(-55));
	AddSequential(new Drive(34,40));
	AddParallel(new IntakeAutoGearScore());
	AddSequential(new Drive(-33,40));
}
void Blue::Retrieval_GetTwoGear()
{
	AddSequential(new Drive(-94,200)); // v 40
	AddSequential(new ArcadeDriveTurn(-50));
	AddSequential(new Drive(-32,80));// v 20
	// scored 1st gear

	AddParallel(new CalibrateArm(false));
	AddSequential(new Drive(60,200)); // v40
	AddSequential(new SetIntake(0.0));
	AddSequential(new ArcadeDriveTurn(52));
	AddParallel(new SetIntakeGear(1.0));
	AddSequential(new Drive(70,200)); // v50
	AddParallel(new StopGearRoll_IntakeUp());
	AddSequential(new Drive(-76,200)); // v50

	// got 2nd gear
	//AddParallel(new SetIntakeGear(0.0));
	//AddParallel(new SetIntakeBall(0.0));
	//AddParallel(new SetIntakeGear(0.0));
	//AddSequential(new Drive(-35,35));

	AddSequential(new ArcadeDriveTurn(112));
	//AddSequential(new Drive(30,30));

	AddSequential(new Drive(64,80));
	//AddParallel(new SetIntakeBall(-0.1));
	AddSequential(new SetIntake(INTAKE_ARM_GEAR_POSITION));
	AddSequential(new Drive(-30, 30));
}
void Blue::Retrieval_GetGear_Shoot()
{

}
//-------------------------------------
