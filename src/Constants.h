/*
 * Constants.h
 *
 *  Created on: Jan 29, 2017
 *      Author: justingriggs
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
constexpr float INTAKE_ARM_ROTATIONS_PER_DEGREE = .1;


#endif /* CONSTANTS_H */
