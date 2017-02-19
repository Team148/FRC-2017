#include "Shooter.h"
#include "../RobotMap.h"

Shooter *Shooter::m_instance = 0;


Shooter::Shooter() : Subsystem("Shooter") {
	std::cout << "Creating Shooter Subsystem" << std::endl;
	m_Motor1 = new CANTalon(SHOOTER_MOTOR_1,1);
	m_Motor2 = new CANTalon(SHOOTER_MOTOR_2,1);

	m_Motor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	m_Motor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);

	m_Motor1->ConfigPeakOutputVoltage(2.0,-12);  	//configure motor to not drive backwards
	m_Motor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_Motor2->ConfigPeakOutputVoltage(2.0,-12);  	//configure motor to not drive backwards
	//m_Motor2->SetClosedLoopOutputDirection(true);	//for reversing follower direction
	m_Motor2->Set(SHOOTER_MOTOR_1);



	m_Motor1->SetSafetyEnabled(false);
	m_Motor2->SetSafetyEnabled(false);



	m_c = new frc::Compressor(0);
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

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Shooter::ConfigureClosedLoop() {
	m_Motor1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	m_Motor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_Motor1->SetSensorDirection(false);
	m_Motor1->SetClosedLoopOutputDirection(false);
	m_Motor1->ConfigEncoderCodesPerRev(256);
	m_Motor1->SetVelocityMeasurementPeriod(CANTalon::VelocityMeasurementPeriod::Period_1Ms);
	m_Motor1->SetVelocityMeasurementWindow(10);
	m_Motor1->SelectProfileSlot(0);
	m_Motor1->SetAllowableClosedLoopErr(0);
//	m_Motor1->SetF(SHOOTER_F);
//	m_Motor1->SetP(SHOOTER_P);
//	m_Motor1->SetD(SHOOTER_D);
	m_Motor1->Set(0);
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
	m_Motor1->Set(-m_rpm);
}

int Shooter::GetRPM() {
	return m_Motor1->GetSpeed();
}

void Shooter::SetFlashlightOn(bool mode)
{
	m_c->SetClosedLoopControl(mode);
}
