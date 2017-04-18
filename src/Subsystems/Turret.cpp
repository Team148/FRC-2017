#include "Turret.h"
//#include "Drivetrain.h"
#include <vector>
#include <cmath>
#include "WPILib.h"

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
static float m_vision_distance_inches = 0.0;
static float m_turret_angle = 0.0;



Turret::Turret() : Subsystem("Turret") {
	std::cout << "info: creating Turret" << std::endl;

	m_Motor = new CANTalon(TURRET_MOTOR);
	m_Motor->SetSafetyEnabled(false);
	m_Motor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_Motor->ConfigPeakOutputVoltage(6.0,-6.0);

	m_HomeSwitch = new frc::DigitalInput(TURRET_HOME_SWITCH);

	m_network_table = NetworkTable::GetTable("GRIP/myContoursReport");
	//m_pc = new PinholeCamera(640, 480, 51.05, 37.9, 0, 64.5);	//FoV determined via experiment
	//m_pc->SetNeutralAxisOffset(-36.0);

//	(float pixel_width, float pixel_height, float FOV_width,
	//		float FOV_height, float angle_offset, float target_height)
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
void Turret::lockTurretAngle(bool lock)
{
	locking = lock;
	static float lockAngle = GetBigAngle() - m_gyro_angle;
	if(lock)
	{
		SetBigAngle((m_gyro_angle +GetBigAngle()));
	}
	else
	{

	}
}

void Turret::TargetBoiler(bool aiming) {

	isAutoAiming = aiming;
	SetBigAngle(GetVisionOffset());
}

void Turret::UpdateNetworkTable() {
	static int target = 0;
	int pix_offset = 0, xRes = 640, yRes = 480;
	int xMid = xRes/2, yMid = yRes/2;
	double targeted = 0.0, targeted2 = 0.0;
	double normalizedWidth, targetWidth;
	double arearatio, widthratio, heightratio;
	static float m_distance = 0;

	constexpr double View_Angle = 41.5, Half_View_Angle = View_Angle/2.0, View_Angle_Height = 37.9; // 44
	constexpr double M_Pi = 3.1415926535898;
	constexpr double ToRadians = M_Pi/180.0;

	constexpr double view_angle_fact = 0.08276; //~ = View_Angle/xRes

	std::vector<double> arr1 = m_network_table->GetNumberArray("area", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr2 = m_network_table->GetNumberArray("centerX", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr3 = m_network_table->GetNumberArray("centerY", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr4 = m_network_table->GetNumberArray("height", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr5 = m_network_table->GetNumberArray("width", llvm::ArrayRef<double>(0.001));

	const unsigned numberOfParticles = 500;

	std::vector<RemoteContourReport> RcRs(numberOfParticles);

	int s1 = arr1.size();
	int s2 = arr2.size();
	int s3 = arr3.size();
	int s4 = arr4.size();
	int s5 = arr5.size();

	if ((s1 > 0) && (s1==s2) && s1==s3 && s1==s4 && s1==s5) {

		for(unsigned int i = 0; i < arr1.size(); i++)
		{
			RcRs[i].Area = arr1[i];
			RcRs[i].CenterX = arr2[i];
			RcRs[i].CenterY = arr3[i];
			RcRs[i].Height = arr4[i];
			RcRs[i].Width = arr5[i];
		}



		std::sort(RcRs.begin(), RcRs.end(), SortByArea); //Sort the result by Area of target


		if((RcRs[1].Area>0.0) && (RcRs[1].Height>0.0) && (RcRs[1].Width>0.0)){
		arearatio = RcRs[0].Area/RcRs[1].Area;
		widthratio = RcRs[0].Width/RcRs[1].Width;
		heightratio = RcRs[0].Height/RcRs[1].Height;
		}
		//if (target == 0) target = 0;
		target = 0;

		if((RcRs[0].Area > 64) && ((widthratio>0.7) && (widthratio<1.3)) && ((heightratio>1.2) && (heightratio<2.0)) ) {
			//Here if we have a valid target
			//Our GRIP processing Image is 640W(x) x 480H(y).  So center of FOV is (x,y) = (160,120).
			//Our target bounding boxes are (Top, Bottom, Left, Right) = (CenterY+Height/2, CenterY-Height/2,...
			//CenterX-Width/2, CenterX+Width/2) where these are target coordinates.
			//We can try just taking the FOV centerX - target CenterX and use that offset to control speed
			//and direction of the turret.  Max delta is 320.
			m_target_valid = true;

			//constexpr float m_FOV_height = (View_Angle_Height*2*M_PI)/360.0;		//converts to radians
			constexpr float m_target_height = 64.5;			//in inches


			float m_neutral_vertical_pixel = -230.9;

			//float m_target_vertical_pixel = yRes/2.0;

			constexpr float m_focal_length = 684.6;


			float m_pitch_angle = atan((yRes - RcRs[0].CenterY - m_neutral_vertical_pixel)/m_focal_length);
			m_distance = m_target_height/tan(m_pitch_angle);


			pix_offset = (xMid - RcRs[0].CenterX);

			//normalizedWidth = float(RcRs[0].Width)/float(xRes);
			//targetWidth = 15.0;  //upper targets are 15"wide by 4" tall

		//m_vision_distance_inches = targetWidth / (normalizedWidth * tan((90 - View_Angle) * ToRadians));

			static float startTime = 0.0;
			if(isAutoAiming)
			{
				if(applyOffset)
				{
					startTime = Timer::GetFPGATimestamp();
					m_vision_angle_offset = ((pix_offset * view_angle_fact) - GetBigAngle());  // +/-22deg
					applyOffset = false;
				}
				if(Timer::GetFPGATimestamp() - startTime >= 0.6)
				{
					applyOffset = true;
				}
				if(applyOffset == false)
				{
					if(GetBigAngle() - abs(m_vision_angle_offset) <= 3.0)
					{
						//applyOffset = true;
					}
				}
			}
			else
			{
				applyOffset = true;
				m_vision_angle_offset = ((pix_offset * view_angle_fact) - GetBigAngle());
			}

			targeted2 = pix_offset * view_angle_fact;  //camera offset from its center in deg
			if(fabs(pix_offset) <= 72.75) {
				targeted = 5.0 - (fabs(pix_offset) * view_angle_fact);
			}
			else targeted = 0.0;
			frc::SmartDashboard::PutNumber("Target detected", targeted2);
			frc::SmartDashboard::PutNumber("Locked On", targeted);
			//frc::SmartDashboard::PutNumber("NormalizedWidth", normalizedWidth);

			//frc::SmartDashboard::PutNumber("Calc_Yaw", m_pc->GetYawAngleDegrees());
			//frc::SmartDashboard::PutNumber("Calc_Dist", m_pc->GetDistance());
			//frc::SmartDashboard::PutNumber("Calc_Pitch", m_pc->GetPitchAngleDegrees());
			frc::SmartDashboard::PutNumber("CenterX", RcRs[0].CenterX);
			//frc::SmartDashboard::PutNumber("CenterY", RcRs[0].CenterY);
		}
		else
			m_target_valid=false;
		//target = target + 1;

		//Publish the sorted 1st two results
		frc::SmartDashboard::PutNumber("VisionTurretPosition", m_vision_angle_offset);
		//frc::SmartDashboard::PutNumber("targetDist_Inches", m_vision_distance_inches);
		frc::SmartDashboard::PutNumber("m_distance", m_distance);
		/*frc::SmartDashboard::PutNumber("ArrayArea1: ", RcRs[0].Area);
		frc::SmartDashboard::PutNumber("ArrayArea2: ", RcRs[1].Area);
		frc::SmartDashboard::PutNumber("ArrayX1: ", RcRs[0].CenterX);
		frc::SmartDashboard::PutNumber("ArrayX2: ", RcRs[1].CenterX);
		//frc::SmartDashboard::PutNumber("ArrayY1: ", RcRs[0].CenterY);
		//frc::SmartDashboard::PutNumber("ArrayY2: ", RcRs[1].CenterY);
		frc::SmartDashboard::PutNumber("ArrayHeight1: ", RcRs[0].Height);
		frc::SmartDashboard::PutNumber("ArrayHeight2: ", RcRs[1].Height);
		frc::SmartDashboard::PutNumber("ArrayWidth1: ", RcRs[0].Width);
		frc::SmartDashboard::PutNumber("ArrayWidt2: ", RcRs[1].Width);
		frc::SmartDashboard::PutNumber("AreaRatio: ", arearatio);
		frc::SmartDashboard::PutNumber("WidthRatio: ", widthratio);
		frc::SmartDashboard::PutNumber("HeightRatio: ", heightratio);
		*/
		frc::SmartDashboard::PutNumber("VectorSize", RcRs.size());
		frc::SmartDashboard::PutNumber("VectorCapacity", RcRs.capacity());

	}

}


bool Turret::IsTargetValid() {
	return m_target_valid;
}

float Turret::GetVisionOffset() {
	return -m_vision_angle_offset;
}


