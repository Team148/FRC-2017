/*
 * Changes1.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: John
 */
#include "Vision/VisionAPI.h"
#include <Vision/CameraServer.h>
#include <Vision/USBCamera.h>

#define USBCAMERA
//#define LOCALCAMERA
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

	bool result;


	// Sort Container by Area function
	bool sortByArea(const RemoteContourReport &lhs, const RemoteContourReport &rhs) { return lhs.Area > rhs.Area; }

>>>>>>>>>>
class Robot: public frc::IterativeRobot {
private:
>>>>>>>>>>
#ifdef LOCALCAMERA
#ifdef AXISCAMERA
	IMAQdxSession session;
	Image *frame;
	Image *binaryFrame;
	int imaqError;
	//	IMAQdxError imaqError;
	std::unique_ptr<AxisCamera> camera;
#endif

#ifdef USBCAMERA
	IMAQdxSession session;
	Image *frame;
	Image *binaryFrame;
	int imaqError;
	nivision::USBCamera *cam0;
	CameraServer *server;
#endif


	//A structure to hold measurements of a particle
	struct ParticleReport {
		double PercentAreaToImageArea;
		double Area;
		double BoundingRectLeft;
		double BoundingRectTop;
		double BoundingRectRight;
		double BoundingRectBottom;
	};

	//Structure to represent the scores for the various tests used for target identification
	struct Scores {
		double Area;
		double Aspect;
	};

	//Constants // duo ring light
//	Range RING_HUE_RANGE = {85, 120};	//Default hue range for ring light
//	Range RING_SAT_RANGE = {67, 255};	//Default saturation range for ring light
//	Range RING_VAL_RANGE = {100, 255};	//Default value range for ring light

//	---UNO RING LIGHT
	Range RING_HUE_RANGE = {81, 146};	//Default hue range for ring light
	Range RING_SAT_RANGE = {29, 255};	//Default saturation range for ring light
	Range RING_VAL_RANGE = {60, 241};	//Default value range for ring light
	//Coverage Area = Bounding box area / strip area.  240/80  in^2.
	//Aspect Ratio = Particle Width / Particle Height - 12"W x 20"H => 1.6.
	//Moment = 0.28 from Moment of Inertia
	//Coordinates (0,0) is top left of screen.  (0,  0) -> (0  ,320)
	//..........................................(0,240) -> (320,240)
	//Aim(x,y) = (P(x,y) - (resolution(x,y)/2) / (resolution(x,y) / 2)
	//Distance
	double AREA_MINIMUM = 0.33; //Default Area minimum for particle as a percentage of total image area
	double AREA_RATIO = (240.0/75.0); //Area of bounding box / area of the tape.
	double RATIO = 0.5; //W/H => 12"/20" -> 0.6.
	double SCORE_MIN = 58.0;  //Minimum score to be considered a target/was 75 /was72 for comp
#ifdef AXISCAMERA
	double VIEW_ANGLE = 64; //View angle fo camera, set to Axis m1011 by default, 64 for m1013, 51.7 for 206, 52 for HD3000 square, 60 for HD3000 640x480
	//using 49 for view angle to correct distance calculation.
#endif
#ifdef USBCAMERA
	double VIEW_ANGLE = 52; //View angle fo camera, set to Axis m1011 by default, 64 for m1013, 51.7 for 206, 52 for HD3000 square, 60 for HD3000 640x480
	//using 49 for view angle to correct distance calculation.
#endif
	ParticleFilterCriteria2 criteria[1];
	ParticleFilterOptions2 filterOptions = {0,0,1,1};
	Scores scores;
	int numParticles = 0;
	float areaMin = 0;
	float bright = 15;
	bool isTarget = 0;
	bool seebinary = 0;
	double TargetAngle = 0.0;
#endif


public:
	std::shared_ptr<NetworkTable> table;


>>>>>>>>>>>
	void RobotInit() override {
		std::cout << "info: starting RobotInit" << std::endl;
>>>>>>>>>>>
		table = NetworkTable::GetTable("GRIP/myContoursReport");


>>>>>>>>>
void DisabledInit() override {
	m_turret_angle=0;
	result = doVisionWithProcessing();

}

>>>>>>>>>>
void DisabledPeriodic() override {
>>>>>>>>>>>
	result = doVisionWithProcessing();

>>>>>>>>>>
void AutonomousInit() override {
>>>>>>>>>>
	result = doVisionWithProcessing();

>>>>>>>>>>
void AutonomousPeriodic() override {
>>>>>>>>>>
	result = doVisionWithProcessing();

>>>>>>>>>>>
void TeleopInit() override {
>>>>>>>>>>>
//		result = doVisionWithProcessing();




bool doVisionWithProcessing()
{
//this is from remote Camera via networktables
	static int target = 0;
	static double angleOff = 0;
	static double pixPDegree = 0;
	static double pixFCenter = 0;
	const unsigned numberOfParticles = 1000;
	double VIEW_ANGLE = 52;

	std::vector<double> arr1 = table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> arr2 = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> arr3 = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> arr4 = table->GetNumberArray("height", llvm::ArrayRef<double>());
	std::vector<double> arr5 = table->GetNumberArray("width", llvm::ArrayRef<double>());

	std::vector<RemoteContourReport> RcRs(numberOfParticles);


	if (arr1.size() > 0){
#define SORT
#ifdef SORT
		for(unsigned int i = 0; i < arr1.size(); i++)
		{
			RcRs[i].Area = arr1[i];
			RcRs[i].CenterX = arr2[i];
			RcRs[i].CenterY = arr3[i];
			RcRs[i].Height = arr4[i];
			RcRs[i].Width = arr5[i];
		}

	std::sort(RcRs.begin(), RcRs.end(), sortByArea); //Sort the result by Area of target
#endif
	//only looking at top two biggest areas.  May need to sort deeper if false targets
	if (target == 4) target = 0;
	if((RcRs[0].Area > 64) && (abs(RcRs[0].Width - RcRs[1].Width) < 7) && (target == 0) ){
	//Here if we have a valid target
	//Our GRIP processing resizes the Image to 640W(x) x 480H(y).  So center of FOV is (x,y) = (160,120).
	//Our target bounding boxes are (Top, Bottom, Left, Right) = (CenterY+Height/2, CenterY-Height/2,...
	//CenterX-Width/2, CenterX+Width/2) where these are target cooridinates.
	//We can try just taking the FOV centerX - target CenterX and use that offset to control speed
	//and direction of the turret.  Max delta is 160.  1/160 is 0.00625

	angle_change = m_turret_angle - (320.0 - RcRs[0].CenterX) * -0.0003;  //.000625 may need to invert this range -0.1 to 0.1
	turret->SetAngle(angle_change);
	m_turret_angle = angle_change;
	}

	target = target + 1;



		//Publish the sorted 1st two results
		frc::SmartDashboard::PutNumber("angleOff", angle_change);
		frc::SmartDashboard::PutNumber("ArrayArea1: ", RcRs[0].Area);
		frc::SmartDashboard::PutNumber("ArrayArea2: ", RcRs[1].Area);
		frc::SmartDashboard::PutNumber("ArrayX1: ", RcRs[0].CenterX);
		frc::SmartDashboard::PutNumber("ArrayX2: ", RcRs[1].CenterX);
		frc::SmartDashboard::PutNumber("ArrayY1: ", RcRs[0].CenterY);
		frc::SmartDashboard::PutNumber("ArrayY2: ", RcRs[1].CenterY);
		frc::SmartDashboard::PutNumber("ArrayHeight1: ", RcRs[0].Height);
		frc::SmartDashboard::PutNumber("ArrayHeight2: ", RcRs[1].Height);
		frc::SmartDashboard::PutNumber("ArrayWidth1: ", RcRs[0].Width);
		frc::SmartDashboard::PutNumber("ArrayWidt2: ", RcRs[1].Width);

	frc::SmartDashboard::PutNumber("Target detected", target);

	}


#ifdef LOCALCAMERA
// here if we want to use a local USB Camera on the RIO
	if(numParticles > 0) {
		//Measure particles and sort by particle size
		std::vector<ParticleReport> particles;
		for(int particleIndex = 0; particleIndex < numParticles; particleIndex++)
		{
			ParticleReport par;
			imaqMeasureParticle(binaryFrame, particleIndex, 0, IMAQ_MT_AREA_BY_IMAGE_AREA, &(par.PercentAreaToImageArea));
			imaqMeasureParticle(binaryFrame, particleIndex, 0, IMAQ_MT_AREA, &(par.Area));
			imaqMeasureParticle(binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_TOP, &(par.BoundingRectTop));
			imaqMeasureParticle(binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_LEFT, &(par.BoundingRectLeft));
			imaqMeasureParticle(binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_BOTTOM, &(par.BoundingRectBottom));
			imaqMeasureParticle(binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_RIGHT, &(par.BoundingRectRight));
			particles.push_back(par);

		}
		sort(particles.begin(), particles.end(), CompareParticleSizes);

		//This example only scores the largest particle. Extending to score all particles and choosing the desired one is left as an exercise
		//for the reader. Note that this scores and reports information about a single particle (single L shaped target). To get accurate information
		//about the location of the tote (not just the distance) you will need to correlate two adjacent targets in order to find the true center of the tote.
		scores.Aspect = AspectScore(particles.at(0));
		SmartDashboard::PutNumber("Aspect", scores.Aspect);
		scores.Area = AreaScore(particles.at(0));
		SmartDashboard::PutNumber("Area", scores.Area);
		isTarget = scores.Area > SCORE_MIN && scores.Aspect > SCORE_MIN;

		//Send distance and tote status to dashboard. The bounding rect, particularly the horizontal center (left - right) may be useful for rotating/driving towards a tote
		SmartDashboard::PutBoolean("IsTarget", isTarget);
		SmartDashboard::PutNumber("Distance", computeDistance(binaryFrame, particles.at(0)));
		//double TargetAngle = 0;

		TargetAngle = 0.1625 * computeAngle(binaryFrame, particles.at(0));  //was 0.161


		SmartDashboard::PutNumber("Target Angle", TargetAngle);

		return isTarget;
	} else {
		SmartDashboard::PutBoolean("IsTarget", false);
		return isTarget;
	}

}


//Comparator function for sorting particles. Returns true if particle 1 is larger
static bool CompareParticleSizes(ParticleReport particle1, ParticleReport particle2)
{
	//we want descending sort order
	return particle1.PercentAreaToImageArea > particle2.PercentAreaToImageArea;
}

/**
 * Converts a ratio with ideal value of 1 to a score. The resulting function is piecewise
 * linear going from (0,0) to (1,100) to (2,0) and is 0 for all inputs outside the range 0-2
 */
double ratioToScore(double ratio)
{
	return (fmax(0, fmin(100*(1-fabs(1-ratio)), 100)));
}


double AreaScore(ParticleReport report)
{
	double boundingArea = (report.BoundingRectBottom - report.BoundingRectTop) * (report.BoundingRectRight - report.BoundingRectLeft);
	//Area of Rect is 240.  Tape is 80sq inches of this
	return ratioToScore((AREA_RATIO)*report.Area/boundingArea);
}

/**
 * Method to score if the aspect ratio of the particle appears to match the retro-reflective target. Target is 12"W x 20"H so aspect should be 1.6
 */
double AspectScore(ParticleReport report)
{
	return ratioToScore((RATIO*(report.BoundingRectRight-report.BoundingRectLeft)/(report.BoundingRectBottom-report.BoundingRectTop)));
}


/**
 * Computes the estimated distance to a target using the width of the particle in the image. For more information and graphics
 * showing the math behind this approach see the Vision Processing section of the ScreenStepsLive documentation.
 *
 * @param image The image to use for measuring the particle estimated rectangle
 * @param report The Particle Analysis Report for the particle
 * @return The estimated distance to the target in feet.
 */
double computeDistance (Image *image, ParticleReport report) {
	double normalizedWidth, targetWidth;
	int xRes, yRes;

	imaqGetImageSize(image, &xRes, &yRes);
	normalizedWidth = 2*(report.BoundingRectRight - report.BoundingRectLeft)/xRes;
	SmartDashboard::PutNumber("Width", normalizedWidth);
	targetWidth = 20;  //targets are 20"wide by 12" tall

	return  targetWidth/(normalizedWidth*12*tan(VIEW_ANGLE*M_PI/(180*2)));
}

double computeAngle (Image *image, ParticleReport report) {
	double normalizedWidth;
	int xRes, yRes;

	imaqGetImageSize(image, &xRes, &yRes);
	normalizedWidth = 2*(report.BoundingRectRight - report.BoundingRectLeft)/xRes;
	SmartDashboard::PutNumber("Width", normalizedWidth);
	SmartDashboard::PutNumber("BoundingRectRight", report.BoundingRectRight);
	SmartDashboard::PutNumber("BoundingRectLeft", report.BoundingRectLeft);
	SmartDashboard::PutNumber("BoundingRectBottom", report.BoundingRectBottom);
	SmartDashboard::PutNumber("BoundingRectTop", report.BoundingRectTop);

	//return  targetWidth/(normalizedWidth*12*tan(VIEW_ANGLE*M_PI/(180*2)));
	return (((report.BoundingRectRight-report.BoundingRectLeft)*0.5)+report.BoundingRectLeft)-165; // 160 for center/ 165 for more left

#endif
	return target;
