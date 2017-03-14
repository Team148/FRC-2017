#include "Turret.h"

Turret *Turret::m_instance = 0;

Turret::Turret() : Subsystem("Turret") {
	std::cout << "info: creating Turret" << std::endl;

	m_Motor = new CANTalon(TURRET_MOTOR);
	m_Motor->SetSafetyEnabled(false);
	m_Motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_Motor->ConfigPeakOutputVoltage(9,-9);

	m_HomeSwitch = new frc::DigitalInput(TURRET_HOME_SWITCH);
}

Turret* Turret::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Turret Class" << std::endl;
		m_instance = new Turret();
	}
	return m_instance;
}

void Turret::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}


void Turret::ConfigClosedLoop() {
	m_Motor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	//if(m_Motor->IsSensorPresent(CANTalon::FeedbackDevice::CtreMagEncoder_Relative) != CANTalon::FeedbackDeviceStatus::FeedbackStatusPresent)
		//std::cout << "error:  could not detect turret sensor" << std::endl;

	m_Motor->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);


	m_Motor->SetSensorDirection(false);
	m_Motor->SetClosedLoopOutputDirection(false);
	m_Motor->SetAllowableClosedLoopErr(0);
	m_Motor->SelectProfileSlot(0);
	m_Motor->SetF(0.0);
	m_Motor->SetP(TURRET_P);
	m_Motor->SetI(TURRET_I);
	m_Motor->SetD(TURRET_D);


	Reset();			//assume starting at Home

	m_Motor->ConfigLimitMode(frc::CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
	m_Motor->ConfigForwardSoftLimitEnable(true);
	m_Motor->ConfigReverseSoftLimitEnable(true);

	m_Motor->ConfigForwardLimit(TURRET_FORWARD_TRAVEL_LIMIT*TURRET_DEG_PER_ROTATION/360);
	m_Motor->ConfigReverseLimit(TURRET_REVERSE_TRAVEL_LIMIT*TURRET_DEG_PER_ROTATION/360);
	m_Motor->Set(0);

	m_isClosedLoop=true;
}


void Turret::ConfigOpenLoop() {
	m_Motor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_Motor->Set(0);
}


void Turret::SetActualPosition(double position) {
	m_Motor->SetPosition(position);
}


void Turret::SetAngle(float angle) {   //sets angle of the motor gear
	m_Motor->Set(angle);
}

void Turret::SetBigAngle(float angle) {  //sets angle of the turret aka big gear
    angle = fmod(angle,360);  //get into 0-360 range
    if (angle < 0) angle += 360;
    angle = fabs(angle);
	// now put into -180 < angle <= 180
	if (angle > 180.0) angle -= 360.0;
	m_Motor->Set(angle * TURRET_DEG_IN_BIG_GEAR);
}

float Turret::GetBigAngle() {
	float angle = m_Motor->Get() * TURRET_INV_DEG_BIG_GEAR;
	return angle;
}

void Turret::Reset() {
	m_Motor->SetPosition(0);
	m_Motor->SetEncPosition(0);
}

bool Turret::IsHomed() {
	return !m_HomeSwitch->Get();
}

bool Turret::IsClosedLoop() {
	return m_isClosedLoop;
}
