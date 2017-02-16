#include "Climber.h"
#include <iostream>
#include "../RobotMap.h"

Climber *Climber::m_instance = 0;

Climber::Climber() : Subsystem("Climber") {
	m_motor = new CANTalon(CLIMBER_MOTOR);
	m_motor->SetSafetyEnabled(false);
	m_motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
}

Climber* Climber::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Climber Class" << std::endl;
		m_instance = new Climber();
	}
	return m_instance;
}

void Climber::InitDefaultCommand() {

}

void Climber::Set(float val) {
	m_motor->Set(val);
}
