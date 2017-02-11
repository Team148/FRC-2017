/*
 * Constants.h
 *
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Drivetrain constants.
constexpr double DRIVETRAIN_F = 0.5645;
constexpr double DRIVETRAIN_P = 0.8;
constexpr float DRIVETRAIN_WHEEL_DIAMETER = 4.0;
constexpr float DRIVETRAIN_BASE_DIAMETER = 39; 		//distance(in) from wheel to wheel

//Auto/Drive
constexpr float DRIVE_GYRO_P = 2.5;

//Auto/TurnPID
constexpr float DRIVE_TURN_P = 0.009;
constexpr float DRIVE_TURN_I = 0.0;
constexpr float DRIVE_TURN_TOLERANCE = 0.05;

//Turret
constexpr float TURRET_ROTATIONS_PER_TICK = 1;


//Intake
constexpr float INTAKE_ARM_ROTATIONS_PER_DEGREE = .0128;
constexpr float INTAKE_ARM_POSITION_P = 0.45;

//Shooter
constexpr float SHOOTER_F = 99.99;
constexpr float SHOOTER_P = 99.99;

#endif /* CONSTANTS_H */
