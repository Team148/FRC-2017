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

//CAN TALON IDs
constexpr int DRIVE_LEFTMOTOR_1 	= 8;
constexpr int DRIVE_LEFTMOTOR_2 	= 9;
constexpr int DRIVE_LEFTMOTOR_3 	= 10;
constexpr int DRIVE_RIGHTMOTOR_1	= 0;
constexpr int DRIVE_RIGHTMOTOR_2 	= 1;
constexpr int DRIVE_RIGHTMOTOR_3 	= 2;

constexpr int SHOOTER_MOTOR_1 		= 3;
constexpr int SHOOTER_MOTOR_2 		= 11;

constexpr int CONVEYOR_LOWER_MOTOR  = 4;
constexpr int CONVEYOR_UPPER_MOTOR  = 5;

constexpr int INTAKE_BALL_MOTOR_1	= 14;
constexpr int INTAKE_GEAR_MOTOR		= 12;
constexpr int INTAKE_ARM_MOTOR		= 13;
constexpr int INTAKE_ARM_DOWN_LIMIT = 0;
constexpr int INTAKE_ARM_UP_LIMIT	= 1;

constexpr int TURRET_MOTOR 			= 6;
constexpr int TURRET_MIN_SWITCH		= 0;
constexpr int TURRET_MAX_SWITCH		= 1;
constexpr int TURRET_HOME_SWITCH	= 2;


#endif  // ROBOTMAP_H
