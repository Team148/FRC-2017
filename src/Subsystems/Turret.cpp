#include "Turret.h"

Turret *Turret::m_instance = 0;

Turret::Turret() : Subsystem("Turret") {
	std::cout << "info: creating Turret" << std::endl;

	m_Motor = new CANTalon(TURRET_MOTOR);
	m_Motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);

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

	//SetForwardLimit
	//SetBackwardLimit
	m_Motor->SetSensorDirection(false);
	m_Motor->SetClosedLoopOutputDirection(true);
	m_Motor->SetAllowableClosedLoopErr(0);
	m_Motor->SelectProfileSlot(0);
	m_Motor->SetF(0.0);
	m_Motor->SetP(TURRET_P);
	m_Motor->SetI(0.0);
	m_Motor->SetD(0.0);

	Reset();			//assume starting at Home
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


void Turret::SetAngle(float angle) {
	//m_Motor->Set(angle*TURRET_ROTATIONS_PER_TICK);
	m_Motor->Set(angle);
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
