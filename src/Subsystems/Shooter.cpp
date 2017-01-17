#include "Shooter.h"
#include "../RobotMap.h"


Shooter::Shooter() : Subsystem("Shooter") {

	m_Motor1 = new CANTalon(SHOOTER_MOTOR_1);
	m_Motor2 = new CANTalon(SHOOTER_MOTOR_2);

	m_Motor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);

	m_Motor2->Set(SHOOTER_MOTOR_1);
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
