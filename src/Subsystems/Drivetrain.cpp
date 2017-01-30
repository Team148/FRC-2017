#include "Drivetrain.h"
#include "Commands/DriveWithJoystick.h"
#include "../RobotMap.h"

Drivetrain *Drivetrain::m_instance = 0;

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

	std::cout << "info: creating drivetrain" << std::endl;
	m_leftMotor1 = new CANTalon(DRIVE_LEFTMOTOR_1);
	m_leftMotor2 = new CANTalon(DRIVE_LEFTMOTOR_2);
	m_leftMotor3 = new CANTalon(DRIVE_LEFTMOTOR_3);
	m_rightMotor1 = new CANTalon(DRIVE_RIGHTMOTOR_1);
	m_rightMotor2 = new CANTalon(DRIVE_RIGHTMOTOR_2);
	m_rightMotor3 = new CANTalon(DRIVE_RIGHTMOTOR_3);

	SetBrakeMode(0);

	m_leftMotor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_leftMotor2->Set(DRIVE_LEFTMOTOR_1);
	m_leftMotor3->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_leftMotor3->Set(DRIVE_LEFTMOTOR_1);

	m_rightMotor2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_rightMotor2->Set(DRIVE_RIGHTMOTOR_1);
	m_rightMotor3->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	m_rightMotor3->Set(DRIVE_RIGHTMOTOR_1);




	m_leftMotor1->SetSafetyEnabled(false);
	m_leftMotor2->SetSafetyEnabled(false);
	m_leftMotor3->SetSafetyEnabled(false);
	m_rightMotor1->SetSafetyEnabled(false);
	m_rightMotor2->SetSafetyEnabled(false);
	m_rightMotor3->SetSafetyEnabled(false);

	m_drive = new RobotDrive(m_leftMotor1, m_rightMotor1);
	m_drive->SetSafetyEnabled(false);

	//PDP
	m_pdp = new PowerDistributionPanel();

	//Gyro
	m_gyro = new ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0);

	m_rightMotor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_rightMotor1->ConfigEncoderCodesPerRev(256); //Set ticks per Revolution
	m_leftMotor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_leftMotor1->ConfigEncoderCodesPerRev(256); //Set ticks per Revolution

}

Drivetrain* Drivetrain::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Drivetrain Class" << std::endl;
		m_instance = new Drivetrain();
	}
	return m_instance;
}

void Drivetrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());

}

void Drivetrain::Arcade(float ystick, float xstick) {
	m_drive->ArcadeDrive(ystick,xstick);
}


void Drivetrain::SetBrakeMode(bool on) {
	if(on) {
		m_leftMotor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		m_leftMotor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		m_leftMotor3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		m_rightMotor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		m_rightMotor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		m_rightMotor3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	}
	else {
		m_leftMotor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftMotor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftMotor3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightMotor1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightMotor2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightMotor3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}
}

void Drivetrain::ConfigureOpenLoop() {
	m_leftMotor1->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	m_leftMotor1->Set(0.0);

	m_rightMotor1->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	m_rightMotor1->Set(0.0);
}
void Drivetrain::ConfigureClosedLoop() {
	m_leftMotor1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	m_leftMotor1->Set(0.0);

	m_rightMotor1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	m_rightMotor1->Set(0.0);
}

void Drivetrain::Reenable() {
	m_leftMotor1->EnableControl();
	m_leftMotor2->EnableControl();
	m_leftMotor3->EnableControl();
	m_rightMotor1->EnableControl();
	m_rightMotor2->EnableControl();
	m_rightMotor3->EnableControl();

}
