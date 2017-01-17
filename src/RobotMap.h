#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

constexpr int DRIVE_LEFTMOTOR_1 	= 0;
constexpr int DRIVE_LEFTMOTOR_2 	= 1;
constexpr int DRIVE_LEFTMOTOR_3 	= 2;
constexpr int DRIVE_RIGHTMOTOR_1	= 3;
constexpr int DRIVE_RIGHTMOTOR_2 	= 4;
constexpr int DRIVE_RIGHTMOTOR_3 	= 5;

constexpr int SHOOTER_MOTOR_1 		= 6;
constexpr int SHOOTER_MOTOR_2 		= 7;

constexpr int CONVEYOR_LOWER_MOTOR  = 8;
constexpr int CONVEYOR_UPPER_MOTOR  = 9;

constexpr int INTAKE_BALL_MOTOR		= 10;
constexpr int INTAKE_GEAR_MOTOR		= 11;
constexpr int INTAKE_ARM_MOTOR		= 12;

constexpr int HANGER_MOTOR			= 13;

#endif  // ROBOTMAP_H
