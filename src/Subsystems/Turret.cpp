#include "Turret.h"

Turret *Turret::m_instance = 0;

//A structure to hold contour measurements a paricle
struct RemoteContourReport {
	double Area;
	double CenterX;
	double CenterY;
	double Height;
	double Width;
};

//Structure to represent the scores for the various tests used for target identification
struct RemoteScores {
	double Area;
	double Aspect;
};


bool SortByArea(const RemoteContourReport &lhs, const RemoteContourReport &rhs)	{
	return lhs.Area > rhs.Area;
};

Turret::Turret() : Subsystem("Turret") {
	std::cout << "info: creating Turret" << std::endl;

	m_Motor = new CANTalon(TURRET_MOTOR);
	m_Motor->SetSafetyEnabled(false);
	m_Motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_Motor->ConfigPeakOutputVoltage(9,-9);

	m_HomeSwitch = new frc::DigitalInput(TURRET_HOME_SWITCH);

	m_network_table = NetworkTable::GetTable("GRIP/myContoursReport");
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
	m_isClosedLoop=false;
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

void Turret::UpdateNetworkTable() {
	int pix_offset = 0;
	std::vector<double> arr1 = m_network_table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> arr2 = m_network_table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> arr3 = m_network_table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> arr4 = m_network_table->GetNumberArray("height", llvm::ArrayRef<double>());
	std::vector<double> arr5 = m_network_table->GetNumberArray("width", llvm::ArrayRef<double>());

	const unsigned numberOfParticles = 1000;
	std::vector<RemoteContourReport> RcRs(numberOfParticles);


	if (arr1.size() > 0) {
		for(unsigned int i = 0; i < arr1.size(); i++)
		{
			RcRs[i].Area = arr1[i];
			RcRs[i].CenterX = arr2[i];
			RcRs[i].CenterY = arr3[i];
			RcRs[i].Height = arr4[i];
			RcRs[i].Width = arr5[i];
		}
	}

	std::sort(RcRs.begin(), RcRs.end(), SortByArea); //Sort the result by Area of target


	if((RcRs[0].Area > 64) && (abs(RcRs[0].Width - RcRs[1].Width) < 7)) {
	//Here if we have a valid target
	//Our GRIP processing resizes the Image to 640W(x) x 480H(y).  So center of FOV is (x,y) = (160,120).
	//Our target bounding boxes are (Top, Bottom, Left, Right) = (CenterY+Height/2, CenterY-Height/2,...
	//CenterX-Width/2, CenterX+Width/2) where these are target cooridinates.
	//We can try just taking the FOV centerX - target CenterX and use that offset to control speed
	//and direction of the turret.  Max delta is 160.  1/160 is 0.00625

		 pix_offset = (320.0 - RcRs[0].CenterX);  //.000625 may need to invert this range -0.1 to 0.1
	}

	//convert offset to degrees
	m_vision_angle_offset = pix_offset*0.00035;
}

float Turret::GetVisionOffset() {
	return m_vision_angle_offset;
}


