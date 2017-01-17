#include "Conveyor.h"
#include "../RobotMap.h"

Conveyor::Conveyor() : Subsystem("Conveyor") {

	m_lowerMotor = new CANTalon(CONVEYOR_LOWER_MOTOR);
	m_upperMotor = new CANTalon(CONVEYOR_UPPER_MOTOR);
}

void Conveyor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
