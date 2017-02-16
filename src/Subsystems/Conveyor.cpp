#include "Conveyor.h"
#include "../RobotMap.h"

Conveyor *Conveyor::m_instance = 0;

Conveyor::Conveyor() : Subsystem("Conveyor") {

	std::cout << "creating Conveyor Subsystem" << std::endl;
	m_lowerMotor = new CANTalon(CONVEYOR_LOWER_MOTOR);
	m_upperMotor = new CANTalon(CONVEYOR_UPPER_MOTOR);

	m_lowerMotor->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);
	m_upperMotor->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);


	m_lowerMotor->SetSafetyEnabled(false);
	m_upperMotor->SetSafetyEnabled(false);
}

Conveyor* Conveyor::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Conveyor Class" << std::endl;
		m_instance = new Conveyor();
	}
	return m_instance;
}

void Conveyor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Conveyor::SetAgitator(float voltage) {
	m_lowerMotor->Set(voltage);

}
void Conveyor::SetKicker(float voltage) {
	m_upperMotor->Set(voltage);


}
