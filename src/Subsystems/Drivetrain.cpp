#include "Drivetrain.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/TankDriveJoystick.h"
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

	//Set All motors to coast
	SetBrakeMode(0);

	//Set Motors 2&3 on both sides to follow Left/Right motor 1
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
	m_gyro->Reset();
	m_gyro->Calibrate();
}

Drivetrain* Drivetrain::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Drivetrain Class" << std::endl;
		m_instance = new Drivetrain();
	}
	return m_instance;
}

void Drivetrain::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystick());
}

void Drivetrain::Arcade(float ystick, float xstick) {
	m_drive->ArcadeDrive(ystick,xstick);
}

void Drivetrain::Tank(float leftstick, float rightstick) {
	m_drive->TankDrive(leftstick,rightstick);
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


double Drivetrain::GetAngle() {
	return m_gyro->GetAngle();
}
int Drivetrain::GetEncoderVelocity() {

	std::cout << "Left enc: "<< m_leftMotor1->GetEncVel() << std::endl;
	std::cout << "Right enc: " << m_rightMotor1->GetEncVel() << std::endl;
	return (m_leftMotor1->GetEncVel() + m_rightMotor1->GetEncVel())/2;


}


void Drivetrain::configClosedLoop() {
	m_leftMotor1->SetControlMode(CANTalon::ControlMode::kSpeed);
	//m_leftMotor1->Set(0.0);
	m_leftMotor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_leftMotor1->ConfigEncoderCodesPerRev(256);
	m_leftMotor1->SetSensorDirection(true);
	m_leftMotor1->SetAllowableClosedLoopErr(0);
	m_leftMotor1->SetClosedLoopOutputDirection(true);
	m_leftMotor1->Set(0.0);
	m_rightMotor1->SetControlMode(CANTalon::ControlMode::kSpeed);
	//m_rightMotor1->Set(0.0);
	m_rightMotor1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_rightMotor1->ConfigEncoderCodesPerRev(256);
	//m_rightMotor1->SetSensorDirection(true);
	m_rightMotor1->SetAllowableClosedLoopErr(0);
	m_rightMotor1->Set(0.0);


	//Setup Ramp Rate
	//m_leftMotor1->SetVoltageRampRate(24);
	//m_rightMotor1->SetVoltageRampRate(24);

	//Set some PIDF values
	m_leftMotor1->SetF(DRIVETRAIN_F);
	m_rightMotor1->SetF(DRIVETRAIN_F);
	m_leftMotor1->SetP(DRIVETRAIN_P);
	m_rightMotor1->SetP(DRIVETRAIN_P);
	m_closedLoop = true;
}

void Drivetrain::ZeroSensors() {
	m_leftMotor1->SetEncPosition(0);
	m_rightMotor1->SetEncPosition(0);
}

bool Drivetrain::isClosedLoop() {
	return m_closedLoop;
}

void Drivetrain::configOpenLoop() {
	m_leftMotor1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_leftMotor1->Set(0);
	m_rightMotor1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_rightMotor1->Set(0);
}

void Drivetrain::SetLeft(float val) {
	m_leftMotor1->Set(val);
}


void Drivetrain::SetRight(float val) {
	m_rightMotor1->Set(val);
}

float Drivetrain::IPStoRPM(float val) {
	//RPM = IPS*60/(circumference of the wheel)
	return (val*60)/(M_PI*DRIVETRAIN_WHEEL_DIAMETER);
}

float Drivetrain::RPMtoIPS(float val) {
	//RPM = IPS*60*Gear_reduction/(circumference of the wheel)
	return (val*M_PI*DRIVETRAIN_WHEEL_DIAMETER)/60;
}

//Returns velocities in RPM
int Drivetrain::GetRightVelocity() {
	return m_rightMotor1->GetEncVel();
}

int Drivetrain::GetLeftVelocity() {
	return m_leftMotor1->GetEncVel();
}

int Drivetrain::GetLeftDistance() {
	return m_leftMotor1->GetEncPosition();
}


int Drivetrain::GetRightDistance() {
	return m_rightMotor1->GetEncPosition();
}


float Drivetrain::RotationtoInch(float val) {
	return val*M_PI*DRIVETRAIN_WHEEL_DIAMETER;
}

float Drivetrain::InchtoRotation(float val) {
	return val/(M_PI*DRIVETRAIN_WHEEL_DIAMETER);
}
