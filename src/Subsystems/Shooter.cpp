#include "Shooter.h"
#include "../RobotMap.h"

Shooter *Shooter::m_instance = 0;


Shooter::Shooter() : Subsystem("Shooter") {
	std::cout << "Creating Shooter Subsystem" << std::endl;
	m_Motor1 = new CANTalon(SHOOTER_MOTOR_1);
	m_Motor2 = new CANTalon(SHOOTER_MOTOR_2);

	m_Motor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_Motor2->Set(SHOOTER_MOTOR_1);

	m_Motor1->SetSafetyEnabled(false);
	m_Motor2->SetSafetyEnabled(false);

	m_Motor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_Motor1->ConfigEncoderCodesPerRev(256); //Set ticks per Revolution  //was 128
	//IF Sensor Needs to be reversed, uncomment next line
	//m_Motor1->SetSensorDirection(true);

	//Set the Maximum output the m_Motor1 is allowed to use.  12 is full power
	m_Motor1->ConfigPeakOutputVoltage(+12,0);
	m_Motor1->ConfigNominalOutputVoltage(0,0);
	m_Motor1->SetAllowableClosedLoopErr(0);   //how much error is allowed, defaults to 0
	m_Motor1->SelectProfileSlot(0);
	double k_F = 0.121;	//0.26 (128 encoder)
	double k_P = 0.5;	//1.4 (128 encoder)
	double k_I = 0.0;
	double k_D = 3.0;	//5.6 (128 encoder)
	m_Motor1->SetF(k_F);  //feed-forward gain
	m_Motor1->SetP(k_P);  //P-gain
	m_Motor1->SetI(k_I);  //I-gain
	m_Motor1->SetD(k_D);  //D-gain

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
void Shooter::ConfigureOpenLoop() {
	m_Motor1->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	m_Motor1->Set(0.0);
}

void Shooter::SetOpenLoop(float value) {
	m_Motor1->Set(value);
}

void Shooter::ConfigureClosedLoop() {
	m_Motor1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	m_Motor1->Set(0.0);
}
void Shooter::SetClosedLoop(float speed) {
	m_Motor1->Set(speed);
}

