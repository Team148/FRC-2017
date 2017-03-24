#include "Turret.h"
#include <vector>
#include <cmath>

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

static float m_vision_angle_offset = 0.0;
constexpr double view_angle_fact = 0.08276;

Turret::Turret() : Subsystem("Turret") {
	std::cout << "info: creating Turret" << std::endl;

	m_Motor = new CANTalon(TURRET_MOTOR);
	m_Motor->SetSafetyEnabled(false);
	m_Motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_Motor->ConfigPeakOutputVoltage(12,-12);

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
	m_Motor->SetVelocityMeasurementPeriod(CANTalon::VelocityMeasurementPeriod::Period_10Ms);
	m_Motor->SetVelocityMeasurementWindow(1);
	m_Motor->SetF(0.0);
	m_Motor->SetP(TURRET_P);
	m_Motor->SetI(TURRET_I);
	m_Motor->SetIzone(TURRET_I_ZONE);
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
	static int target = 0;
	int pix_offset = 0;
	double targeted = 0.0, targeted2 = 0.0;

	std::vector<double> arr1 = m_network_table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> arr2 = m_network_table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	//std::vector<double> arr3 = m_network_table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	//std::vector<double> arr4 = m_network_table->GetNumberArray("height", llvm::ArrayRef<double>());
	std::vector<double> arr5 = m_network_table->GetNumberArray("width", llvm::ArrayRef<double>());

	const unsigned numberOfParticles = 1000;

	std::vector<RemoteContourReport> RcRs(numberOfParticles);

	int s1 = arr1.size();
	int s2 = arr2.size();
	//int s3 = arr3.size();
	//int s4 = arr4.size();
	int s5 = arr5.size();

	if ((arr1.size() > 0) && (s1==s2) && s1==s5) {

		for(unsigned int i = 0; i < arr1.size(); i++)
		{
			RcRs[i].Area = arr1[i];
			RcRs[i].CenterX = arr2[i];
			//RcRs[i].CenterY = arr3[i];
			//RcRs[i].Height = arr4[i];
			RcRs[i].Width = arr5[i];
		}

		std::sort(RcRs.begin(), RcRs.end(), SortByArea); //Sort the result by Area of target

		if (target == 25) target = 0;
		//target = 0;
		if((RcRs[0].Area > 64) && (abs(RcRs[0].Width - RcRs[1].Width) < 10) && (target == 0) ) {
			//Here if we have a valid target
			//Our GRIP processing resizes the Image to 640W(x) x 480H(y).  So center of FOV is (x,y) = (160,120).
			//Our target bounding boxes are (Top, Bottom, Left, Right) = (CenterY+Height/2, CenterY-Height/2,...
			//CenterX-Width/2, CenterX+Width/2) where these are target coordinates.
			//We can try just taking the FOV centerX - target CenterX and use that offset to control speed
			//and direction of the turret.  Max delta is 160.  1/160 is 0.00625

			pix_offset = (320.0 - RcRs[0].CenterX);

			m_vision_angle_offset = (((320.0 - RcRs[0].CenterX) * 0.08125) - GetBigAngle());  // +/-22deg

			targeted2 = pix_offset * view_angle_fact;
			if(fabs(pix_offset) <= 72.75) {
				targeted = 5.0 - (fabs(pix_offset) * view_angle_fact);
			}
			else targeted = 0.0;
			frc::SmartDashboard::PutNumber("Target detected", targeted2);
			frc::SmartDashboard::PutNumber("Locked On", targeted);
		}
		target = target + 1;

		//Publish the sorted 1st two results
		frc::SmartDashboard::PutNumber("angleOff", m_vision_angle_offset);
		frc::SmartDashboard::PutNumber("ArrayArea1: ", RcRs[0].Area);
		frc::SmartDashboard::PutNumber("ArrayArea2: ", RcRs[1].Area);
		frc::SmartDashboard::PutNumber("ArrayX1: ", RcRs[0].CenterX);
		frc::SmartDashboard::PutNumber("ArrayX2: ", RcRs[1].CenterX);
		//frc::SmartDashboard::PutNumber("ArrayY1: ", RcRs[0].CenterY);
		//frc::SmartDashboard::PutNumber("ArrayY2: ", RcRs[1].CenterY);
		//frc::SmartDashboard::PutNumber("ArrayHeight1: ", RcRs[0].Height);
		//frc::SmartDashboard::PutNumber("ArrayHeight2: ", RcRs[1].Height);
		frc::SmartDashboard::PutNumber("ArrayWidth1: ", RcRs[0].Width);
		frc::SmartDashboard::PutNumber("ArrayWidt2: ", RcRs[1].Width);

	}

}

void Turret::TargetBoiler(bool isAiming) {
	if(isAiming) SetBigAngle(GetVisionOffset());
}

float Turret::GetVisionOffset() {
	return m_vision_angle_offset;
}


