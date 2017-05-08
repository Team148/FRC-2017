/*
 * Constants.h
 *
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H


//Drivetrain constants.
constexpr double DRIVETRAIN_F = .95;//.95;
constexpr double DRIVETRAIN_P = 1.5; // 1.5
constexpr double DRIVETRAIN_I = 0.001; // 0.005
//constexpr double DRIVETRAIN_I_ZONE_L = 128.0;
//constexpr double DRIVETRAIN_I_ZONE_R = 128.0;

constexpr double DRIVETRAIN_D = 0.0;
constexpr float DRIVETRAIN_WHEEL_DIAMETER = 4.0;
constexpr float DRIVETRAIN_BASE_DIAMETER = 39; 		//distance(in) from wheel to wheel
constexpr float DRIVETRAIN_GEAR_REDUCTION = 66/12;

constexpr float DRIVETRAIN_MAX_ACCEL = 100; 		//Inches per sec^2
constexpr float DRIVETRAIN_MAX_DECEL = 90;		//Inches per sec^2
constexpr float DRIVETRAIN_MAX_VEL = 150; //Inches per sec

//Auto/DriveStraightTMP
constexpr double kDriveHeadingVelocityKp = 4.0;
constexpr double kDriveHeadingVelocityKi = 0.0;
constexpr double kDriveHeadingVelocityKd = 50.0;

//Auto/Drive
constexpr float DRIVE_GYRO_P = 15.0; //
constexpr float DRIVE_VELOCITY_P = .0;

//Auto/TurnPID
constexpr float DRIVE_TURN_P = 0.01;
constexpr float DRIVE_TURN_I = 0.000;
constexpr float DRIVE_TURN_TOLERANCE = 0.05;

//Auto/TurnTMP
constexpr float TURN_DIST_P = 0.05;

//Auto/ArcadeDriveTurn
constexpr float ARCADE_TURN_P = 0.092; // 0.920
constexpr float ARCADE_TURN_I = 0.472; // 0.472
constexpr float ARCADE_TURN_TOLERANCE = 0.05;

//Auto/ArcadeDriving
constexpr float ARCADE_DRIVE_P = 0.1;
constexpr float ARCADE_DRIVE_I = 0.02;
constexpr float ARCADE_DRIVE_GYRO_P = 0.02;

//Turret
constexpr float TURRET_DEG_PER_ROTATION = 475.0/27.0;
constexpr float TURRET_DEG_IN_BIG_GEAR = TURRET_DEG_PER_ROTATION * 0.002777778;  // 1/360= .0027...
constexpr float TURRET_INV_DEG_BIG_GEAR = 20.463156;
constexpr float TURRET_P = 0.5; //0.7
constexpr float TURRET_I = 0.000; // 0.002
constexpr float TURRET_I_ZONE = 0.0;
constexpr float TURRET_D = 0.0; //30.0
constexpr float TURRET_SPEED = 0.432;
constexpr float TURRET_FORWARD_TRAVEL_LIMIT = 100;		//forward limit of travel in Degrees
constexpr float TURRET_REVERSE_TRAVEL_LIMIT = -100;		//reverse limit of travel in Degrees
constexpr float TURRET_JOYSTICK_DEADBAND = 0.1;


//Intake
constexpr float INTAKE_ARM_ROTATIONS_PER_DEGREE = 84/18/360;
constexpr float INTAKE_ARM_POSITION_P = 0.35;
constexpr float INTAKE_ARM_POSITION_I = 0.000;
constexpr float INTAKE_ARM_POSITION_D = 3.75;
constexpr float INTAKE_ARM_POSITION_UP = 0.0;
constexpr float INTAKE_ARM_GEAR_POSITION = -0.9; //was 0.6 before houston north
constexpr float INTAKE_ARM_POSITION_DOWN = -1.450; // 1.383 1.463
constexpr float INTAKE_ARM_DOWN_VOLTAGE = -12.0;
constexpr float INTAKE_ARM_OPEN_LOOP_SPEED = 0.80;

//Conveyer
constexpr float CONVEYER_AGITATOR_VOLTAGE = 6.0;
constexpr float CONVEYER_KICKER_VOLTAGE = -1.0;

//Shooter
constexpr float SHOOTER_F = 0.0333; // 0.0575
constexpr float SHOOTER_P = 0.25; // 0.3
constexpr float SHOOTER_D = 0.3;

constexpr int SHOOTER_SET_POINT_A = 2700;
constexpr int SHOOTER_SET_POINT_B = 3320; // 4185

constexpr float SHOOTING_POSITION_BLUE = 7.0;
constexpr float SHOOTING_POSITION_RED = -7.0;

constexpr int SHOOTER_PRACTICE_FUDGE_FACTOR = 0;//-10;

//AUTON

	//	auto naming standards
	//  POSITION_ACTION_ACTION_ACTION...
	//	POSITION_POSITION_ACTION_ACTION...

constexpr double FAST_SCHEDULER_PERIOD = 1.0/100.0; //100Hz 10ms Loop

constexpr int	BOILER_GEAR = 0;
constexpr int	BOILER_GEAR_HOPPER_SHOOT = 1;
constexpr int	BOILER_HOPPER_SHOOT = 2;
constexpr int	BOILER_TWO_GEAR = 3;
constexpr int	BOILER_GEAR_SHOOT = 4;


constexpr int	CENTER_GEAR = 10;
constexpr int	CENTER_TWO_GEAR = 11;
constexpr int 	CENTER_TWO_GEAR_NOSCORE = 12;
constexpr int 	CENTER_TWO_GEAR_NOSCORE_SHOOT = 13;
constexpr int	CENTER_GEAR_SHOOT = 14;



constexpr int	RETRIEVAL_GEAR = 20;
constexpr int	RETRIEVAL_TWOGEAR = 21;
constexpr int 	RETRIEVAL_GEAR_SHOOT = 22;

constexpr int	RED = 1;
constexpr int	BLUE = 0;

constexpr int	POSITION_BOILER = 1;
constexpr int	POSITION_CENTER = 2;
constexpr int	POSITION_RETRIEVAL = 3;



#endif /* CONSTANTS_H */
