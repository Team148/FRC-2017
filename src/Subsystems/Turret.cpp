#include "Turret.h"

Turret *Turret::m_instance = 0;

Turret::Turret() : Subsystem("Turret") {
	std::cout << "info: creating Turret" << std::endl;

	m_Motor = new CANTalon(TURRET_MOTOR);
	m_Motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);

	m_HomeSwitch = new DigitalInput(TURRET_HOME_SWITCH);
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

	m_Motor->SetSensorDirection(true);
	m_Motor->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);
	m_Motor->Set(0);

	//SetForwardLimit
	//SetBackwardLimit
	m_Motor->SetAllowableClosedLoopErr(0);
	m_Motor->SelectProfileSlot(0);
	m_Motor->SetF(0.0);
	m_Motor->SetP(0.1);
	m_Motor->SetI(0.0);
	m_Motor->SetD(0.0);
}


void Turret::ConfigOpenLoop() {
	m_Motor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
}


void Turret::SetActualPosition(double position) {
	m_Motor->SetPosition(position);
}


void Turret::SetAngle(float angle) {
	float radians = angle*M_PI/180;
	m_Motor->Set(radians/(2*M_PI * TURRET_ROTATIONS_PER_TICK));
}
