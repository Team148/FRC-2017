/*
 * Constants.h
 *
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Drivetrain constants.
constexpr double DRIVETRAIN_F = .68;
constexpr double DRIVETRAIN_P = 0.4;
constexpr float DRIVETRAIN_WHEEL_DIAMETER = 4.0;
constexpr float DRIVETRAIN_BASE_DIAMETER = 39; 		//distance(in) from wheel to wheel
constexpr float DRIVETRAIN_GEAR_REDUCTION = 66/12;

//Auto/Drive
constexpr float DRIVE_GYRO_P = 2.55;
constexpr float DRIVE_VELOCITY_P = .0;

//Auto/TurnPID
constexpr float DRIVE_TURN_P = 0.009;
constexpr float DRIVE_TURN_I = 0.0;
constexpr float DRIVE_TURN_TOLERANCE = 0.02;

//Auto/TurnTMP
constexpr float TURN_DIST_P = 0.05;

//Auto/ArcadeDriveTurn
constexpr float ARCADE_TURN_P = 0.17;
constexpr float ARCADE_TURN_I = 0.006;
constexpr float ARCADE_TURN_TOLERANCE = 0.015;

//Turret
constexpr float TURRET_DEG_PER_ROTATION = 190/11;
constexpr float TURRET_P = 0.5;
constexpr float TURRET_SPEED = 0.025;
constexpr float TURRET_FORWARD_TRAVEL_LIMIT = 100;		//forward limit of travel in Degrees
constexpr float TURRET_REVERSE_TRAVEL_LIMIT = -90;		//reverse limit of travel in Degrees
constexpr float TURRET_JOYSTICK_DEADBAND = 0.1;


//Intake
constexpr float INTAKE_ARM_ROTATIONS_PER_DEGREE = 84/18/360;
constexpr float INTAKE_ARM_POSITION_P = 0.55;
constexpr float INTAKE_ARM_POSITION_I = 0.0001;
constexpr float INTAKE_ARM_POSITION_UP = 1.12;
constexpr float INTAKE_ARM_DOWN_VOLTAGE = -5.75;
constexpr float INTAKE_ARM_OPEN_LOOP_SPEED = 0.77;

//Conveyer
constexpr float CONVEYER_AGITATOR_VOLTAGE = 8.75;
constexpr float CONVEYER_KICKER_VOLTAGE = 10.0;

//Shooter
constexpr float SHOOTER_F = 0.12;
constexpr float SHOOTER_P = 0.52;
constexpr float SHOOTER_D = 2.0;

constexpr int SHOOTER_SET_POINT_A = 3260;
constexpr int SHOOTER_SET_POINT_B = 3580;

#endif /* CONSTANTS_H */
