#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() : Subsystem("Intake") {

	m_ArmMotor = new CANTalon(INTAKE_ARM_MOTOR);
	m_GearMotor = new CANTalon(INTAKE_GEAR_MOTOR);
	m_BallMotor = new CANTalon(INTAKE_BALL_MOTOR);

}

void Intake::InitDefaultCommand() {

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
