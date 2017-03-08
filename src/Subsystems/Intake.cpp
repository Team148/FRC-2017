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

	m_UpLimit = new frc::DigitalInput(INTAKE_ARM_UP_LIMIT);
	m_DownLimit = new frc::DigitalInput(INTAKE_ARM_DOWN_LIMIT);

	m_beam = new frc::AnalogInput(INTAKE_BEAM_BREAK_AN_IN);
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
	m_isClosedLoop = 0;
}

void Intake::ConfigureClosedLoop() {
	m_ArmMotor->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);
	m_ArmMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	m_ArmMotor->SetSensorDirection(false);
	m_ArmMotor->SetClosedLoopOutputDirection(false);
	m_ArmMotor->SetAllowableClosedLoopErr(0);
	m_ArmMotor->SelectProfileSlot(0);
	m_ArmMotor->ConfigPeakOutputVoltage(12.0,INTAKE_ARM_DOWN_VOLTAGE);  //Forward is Up
	m_ArmMotor->SetF(0.0);
	m_ArmMotor->SetP(INTAKE_ARM_POSITION_P);
	m_ArmMotor->SetI(INTAKE_ARM_POSITION_I);
	m_ArmMotor->SetD(0.0);
	ResetArm(0.0);
	m_isClosedLoop = 1;
}

bool Intake::IsClosedLoop() {
	return m_isClosedLoop;
}
void Intake::SetCalibrating(bool calibrate)
{
	m_calibrating = calibrate;
}

bool Intake::IsCalibrating()
{
	return m_calibrating;
}

bool Intake::IsIntakeUp() {

	if(m_UpLimit)
		return true;
	else
		return false;
}


bool Intake::IsIntakeDown() {
	return !m_DownLimit->Get();
}


void Intake::ResetArm(float actual_pos) {
	m_ArmMotor->SetPosition(actual_pos);
}

void Intake::SetArmAngle(float angle) {
	if(m_isClosedLoop)
		m_ArmMotor->Set(angle);
	//std::cout << angle*INTAKE_ARM_ROTATIONS_PER_DEGREE << std::endl;
}

float Intake::GetArmAngle() {
	return m_ArmMotor->GetPosition();
}


bool Intake::IsBeamBroke() {
	frc::SmartDashboard::PutNumber("BeamVoltage",m_beam->GetVoltage());
	if(m_beam->GetVoltage() > 3.0)
		return 1;
	if(m_beam->GetVoltage() < 3.0)
		return 0;
}
