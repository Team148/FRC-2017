/*
 * Constants.h
 *
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Drivetrain constants.
constexpr double DRIVETRAIN_F = 0.5645;
constexpr double DRIVETRAIN_P = 0.7;
constexpr float DRIVETRAIN_WHEEL_DIAMETER = 4.0;
constexpr float DRIVETRAIN_BASE_DIAMETER = 39; 		//distance(in) from wheel to wheel
constexpr float DRIVETRAIN_GEAR_REDUCTION = 66/12;

//Auto/Drive
constexpr float DRIVE_GYRO_P = 2.55;
constexpr float DRIVE_VELOCITY_P = .5;

//Auto/TurnPID
constexpr float DRIVE_TURN_P = 0.009;
constexpr float DRIVE_TURN_I = 0.0;
constexpr float DRIVE_TURN_TOLERANCE = 0.05;

//Turret
constexpr float TURRET_ROTATIONS_PER_TICK = 1;
constexpr float TURRET_P = .2;


//Intake
constexpr float INTAKE_ARM_ROTATIONS_PER_DEGREE = 84/18/360;
constexpr float INTAKE_ARM_POSITION_P = 0.55;
constexpr float INTAKE_ARM_POSITION_I = 0.0001;
constexpr float INTAKE_ARM_DOWN_VOLTAGE = -5.75;

//Shooter
constexpr float SHOOTER_F = 99.99;
constexpr float SHOOTER_P = 99.99;

#endif /* CONSTANTS_H */
