#include "Intake.h"
#include "../RobotMap.h"

Intake *Intake::m_instance = 0;

Intake::Intake() : Subsystem("Intake") {

	m_ArmMotor = new CANTalon(INTAKE_ARM_MOTOR);
	m_GearMotor = new CANTalon(INTAKE_GEAR_MOTOR);
	m_BallMotor_1 = new CANTalon(INTAKE_BALL_MOTOR_1);

	m_ArmMotor->SetSafetyEnabled(false);
	m_GearMotor->SetSafetyEnabled(false);
	m_BallMotor_1->SetSafetyEnabled(false);

	m_ArmMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	m_ArmMotor->ConfigEncoderCodesPerRev(4096);
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

void Intake::SetArm(float val) {
	m_ArmMotor->Set(val);
}

void Intake::SetGear(float val) {
	m_GearMotor->Set(val);
}

void Intake::SetBall(float val) {
	m_BallMotor_1->Set(val);
}
void Intake::ConfigureOpenLoop() {
	m_ArmMotor->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	m_ArmMotor->Set(0.0);
}

void Intake::ConfigureClosedLoop() {
	m_ArmMotor->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	m_ArmMotor->Set(0.0);
}

bool Intake::IsIntakeUp() {

	if(m_UpLimit) return true; else return false;
}
bool Intake::IsIntakeDown() {

	if(m_DownLimit)
		{
			m_ArmMotor->SetPosition(0.0);
			return true;
		}
	 else return false;

}
