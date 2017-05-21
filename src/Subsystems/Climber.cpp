#include "Climber.h"
#include <iostream>
#include "../RobotMap.h"

Climber *Climber::m_instance = 0;

Climber::Climber() : Subsystem("Climber") {

	m_climberMotor = new CANTalon(CLIMBER_MOTOR);
	m_climberMotor2 = new CANTalon(CLIMBER_MOTOR_2);

	m_climberMotor->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);
	m_climberMotor2->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);
	m_climberMotor->ConfigPeakOutputVoltage(12.0,-12); //climber ONLY goes backwards
	m_climberMotor2->ConfigPeakOutputVoltage(12.0,-12);

	m_climberMotor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_climberMotor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);


	m_climberMotor->SetSafetyEnabled(false);
	m_climberMotor2->SetSafetyEnabled(false);
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

void Climber::Set(float voltage) {
	m_climberMotor->Set(voltage);
	m_climberMotor2->Set(-voltage);}
