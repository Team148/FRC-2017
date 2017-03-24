#include "Shooter.h"
#include "../RobotMap.h"

Shooter *Shooter::m_instance = 0;


Shooter::Shooter() : Subsystem("Shooter") {
	std::cout << "Creating Shooter Subsystem" << std::endl;
	m_Motor1 = new CANTalon(SHOOTER_MOTOR_1,1);
	m_Motor2 = new CANTalon(SHOOTER_MOTOR_2,1);

	m_Motor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	m_Motor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);

	m_Motor1->ConfigPeakOutputVoltage(12.0,0.0);  	//configure motor to not drive backwards
	m_Motor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_Motor2->ConfigPeakOutputVoltage(12.0,0.0);  	//configure motor to not drive backwards
	m_Motor2->Set(SHOOTER_MOTOR_1);



	m_Motor1->SetSafetyEnabled(false);
	m_Motor2->SetSafetyEnabled(false);


	m_flashlight = new frc::Solenoid(FLASHLIGHT_SOLENOID);
	m_ringlight = new frc::Solenoid(VISION_LIGHT_SOLENOID);
}

Shooter* Shooter::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Shooter Class" << std::endl;
		m_instance = new Shooter();
	}
	return m_instance;
}


void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}


void Shooter::ConfigureClosedLoop() {
	m_Motor1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	m_Motor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_Motor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	m_Motor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	m_Motor1->SetSensorDirection(true);
	m_Motor1->SetClosedLoopOutputDirection(false);
	m_Motor1->ConfigEncoderCodesPerRev(256);
	m_Motor1->SetVelocityMeasurementPeriod(CANTalon::VelocityMeasurementPeriod::Period_50Ms);
	m_Motor1->SetVelocityMeasurementWindow(32);
	m_Motor1->SelectProfileSlot(0);
	m_Motor1->SetAllowableClosedLoopErr(0);
	m_Motor1->SetF(SHOOTER_F);
	m_Motor1->SetP(SHOOTER_P);
	m_Motor1->SetD(SHOOTER_D);
	m_Motor1->Set(0);

	m_Motor1->DisableNominalClosedLoopVoltage();
	m_Motor2->DisableNominalClosedLoopVoltage();
	m_Motor1->SetNominalClosedLoopVoltage(12.0f);
	m_Motor2->SetNominalClosedLoopVoltage(12.0f);

	m_isClosedLoop = true;
}


void Shooter::ConfigureOpenLoop() {
	m_Motor1->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	m_Motor1->Set(0.0);
}


void Shooter::SetOpenLoop(float value) {
	m_Motor1->Set(value);
}

void Shooter::SetRPM(int rpm) {
	m_rpm = rpm;
	m_Motor1->Set(m_rpm);
}

int Shooter::GetRPM() {
	return m_Motor1->GetSpeed();
}
float Shooter::GetCurrent() {
	return m_Motor1->GetOutputCurrent();
}
float Shooter::GetVoltage() {
	return m_Motor1->GetOutputVoltage();
}

void Shooter::SetFlashlightOn(bool on)
{
	if(on)
		SetRingLightOn(0);
	m_flashlight->Set(on);
}

void Shooter::SetRingLightOn(bool on)
{
	if(on)
		SetFlashlightOn(0);
	m_ringlight->Set(on);
}
