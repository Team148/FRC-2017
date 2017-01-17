#include "Drivetrain.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

	m_leftMotor1 = new CANTalon(DRIVE_LEFTMOTOR_1);
	m_leftMotor2 = new CANTalon(DRIVE_LEFTMOTOR_2);
	m_leftMotor3 = new CANTalon(DRIVE_LEFTMOTOR_3);
	m_rightMotor1 = new CANTalon(DRIVE_RIGHTMOTOR_1);
	m_rightMotor2 = new CANTalon(DRIVE_RIGHTMOTOR_2);
	m_rightMotor3 = new CANTalon(DRIVE_RIGHTMOTOR_3);

	m_leftMotor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_leftMotor3->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);

	m_rightMotor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_rightMotor3->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);

	m_leftMotor2->Set(DRIVE_LEFTMOTOR_1);
	m_leftMotor3->Set(DRIVE_LEFTMOTOR_1);
	m_rightMotor2->Set(DRIVE_RIGHTMOTOR_1);
	m_rightMotor3->Set(DRIVE_RIGHTMOTOR_1);
}

void Drivetrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
