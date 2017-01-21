#include "Intake.h"
#include "../RobotMap.h"

Intake *Intake::m_instance = 0;

Intake::Intake() : Subsystem("Intake") {

	m_ArmMotor = new CANTalon(INTAKE_ARM_MOTOR);
	m_GearMotor = new CANTalon(INTAKE_GEAR_MOTOR);
	m_BallMotor = new CANTalon(INTAKE_BALL_MOTOR);

	m_ArmMotor->SetSafetyEnabled(false);
	m_GearMotor->SetSafetyEnabled(false);
	m_BallMotor->SetSafetyEnabled(false);
}


Intake* Intake::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Intake Class" << std::endl;
		m_instance = new Intake();
	}
	return m_instance;
}


void Intake::InitDefaultCommand() {

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
