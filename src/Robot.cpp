#include <memory>
#include <iostream>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Util/logger.h"

#include "CommandBase.h"
#include "Commands/Auto/Drive.h"
#include "Commands/Auto/Autonomous.h"
#include "commands/Auto/Center1Gear.h"
#include "Commands/Auto/CalibrateArm.h"
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


class Robot: public frc::IterativeRobot {
private:
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

	Drivetrain *drivetrain = 0;
	OI* oi = 0;
	Conveyor* conveyor = 0;
	Intake* intake = 0;
	Shooter* shooter = 0;
	Turret* turret = 0;
	Climber* climber = 0;
	Logger* log = 0;

	void RobotInit() override {
		std::cout << "info: starting RobotInit" << std::endl;

		table = NetworkTable::GetTable("GRIP/myContoursReport");

		oi = OI::GetInstance();
		drivetrain = Drivetrain::GetInstance();
		conveyor = Conveyor::GetInstance();
		intake = Intake::GetInstance();
		shooter = Shooter::GetInstance();
		turret = Turret::GetInstance();
		climber = Climber::GetInstance();
		log = new Logger();



		//chooser.AddDefault("Default Auto", new ExampleCommand());
		// chooser.AddObject("My Auto", new MyAutoCommand());
		//frc::SmartDashboard::PutData("Auto Modes", &chooser);

	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {
		result = doVisionWithProcessing();
	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();

		result = doVisionWithProcessing();

		SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		}
		else {
			autonomousCommand.reset(new ExampleCommand());
		} */

		//autonomousCommand.reset(chooser.GetSelected());

		//if (autonomousCommand.get() != nullptr) {
		//	autonomousCommand->Start();
		//}
		log->Start();
		drivetrain->configClosedLoop();
		//frc::Scheduler::GetInstance()->AddCommand(new Center1Gear());
		frc::Scheduler::GetInstance()->AddCommand(new Autonomous());

		result = doVisionWithProcessing();
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		//frc::SmartDashboard::PutNumber("Drive Left Encoder Velocity: ", drivetrain->GetLeftVelocity());
		//frc::SmartDashboard::PutNumber("Drive Right Encoder Velocity: ", drivetrain->GetRightVelocity());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		std::cout << "starting TeleopInit" << std::endl;
		result = doVisionWithProcessing();

		//Set Shooter for OpenLoop
		shooter->ConfigureOpenLoop();
		//uncomment for ClosedLoop Shooter
		//shooter->ConfigureClosedLoop();
		drivetrain->configOpenLoop();
		turret->ConfigClosedLoop();
		if(!intake->IsClosedLoop())
			frc::Scheduler::GetInstance()->AddCommand(new CalibrateArm());

		//if (autonomousCommand != nullptr) {
		//	autonomousCommand->Cancel();
		//}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();

		static float ballIntake = 0.0;
		static float gearIntake = 0.0;
		static float armMotor = 0.0;
		static float agitator = 0.0;
		static float kicker = 0.0;
		static int shooterRpm = 0;
		constexpr int shooterSetPoint_A = 3000;
		constexpr int shooterSetPoint_B = 2500;

		//Manual Open Loop Controls
		//Drive control is in Commands/DriveWithJoystick
		ballIntake = 0.0;
		gearIntake = 0.0;
		agitator = 0.0;
		kicker = 0.0;
		armMotor = 0.0;


		result = doVisionWithProcessing();

		if(oi->opStick->GetRawButton(2))
		{
			ballIntake = 1.0;
		}
		if(oi->opStick->GetRawButton(3))
		{
			ballIntake = -1.0;
		}//Ball Intake

		intake->SetBall(ballIntake);

		if(oi->opStick->GetRawButton(1))
		{
			gearIntake = 1.0;
		}		//GearIntake
		if(oi->opStick->GetRawButton(4))
		{
			gearIntake = -1.0;
		}		//GearIntake Out
		intake->SetGear(gearIntake);

		//AGITATOR AND SHOOTER FIRE
		if(oi->opStick->GetRawButton(5))
		{
			agitator = 10.0;
		}	//Run Agitator (Voltage control)
		if(oi->opStick->GetRawButton(6))
		{
			agitator = 10.0;
			kicker = 10.0;
		}	//Run Agitator (Voltage control)

		conveyor->SetAgitator(agitator);
		conveyor->SetKicker(kicker);
		//END AGITATOR AND FIRE


		//CLOSED LOOP ARM CODE
		//Shoulder Buttons
		if(intake->IsClosedLoop()) {
			if(oi->drvStick->GetRawButton(6)){
				//intake->SetArmAngle(0.0); //down
				m_armAngle=0;
			}
			if(oi->drvStick->GetRawButton(5)) {
				//intake->SetArmAngle(1.12); //up
				m_armAngle=1.12;
			}

			//increment Arm Up/Down
			if(oi->drvStick->GetRawButton(2)) {
				m_armAngle -= 0.025;
			}

			if(oi->drvStick->GetRawButton(4)) {
				m_armAngle += 0.025;
			}

		intake->SetArmAngle(m_armAngle);
		}
		else {  //OPEN LOOP INTAKE
			if(oi->drvStick->GetRawButton(6)){
				//down
				armMotor=-.77;
			}
			if(oi->drvStick->GetRawButton(5)) {
				//up
				armMotor=.77;
			}
		intake->SetArm(armMotor);
		}
		//END INTAKE ARM



		//OPEN LOOP SHOOTER
//		if(oi->opStick->GetRawButton(6)){shooteron=true;}	//Run Shooter
//
//		if(shooteron) { shooter->SetOpenLoop(0.8); }  		//setShooter to ShooterSetpoint
//		else {shooter->SetOpenLoop(0); }					//SetShooter 0

		if(oi->opStick->GetRawAxis(1) <= -1)
		{
			shooterRpm -= 10;
		}



		//CLOSED LOOP SHOOTER
		if(oi->opStick->GetRawAxis(1) >= 1) //RPM adjust up
		{
			shooterRpm += 10;
		}

		if(oi->opStick->GetRawAxis(1) <= -1) //RPM adjust down
		{
			shooterRpm -= 10;
		}

		if(oi->opStick->GetRawAxis(0) >= 1)
		{
			shooterRpm = shooterSetPoint_A;
		}
		if(oi->opStick->GetRawAxis(0) <= -1)
		{
			shooterRpm = shooterSetPoint_B;
		}
		if(oi->opStick->GetRawButton(9))	//Turret off
		{
			shooterRpm = 0;
		}
		shooter->SetRPM(shooterRpm);
		//END CLOSEDLOOP SHOOTER

		//TURRET
		float angle_change = m_turret_angle + oi->opStick->GetRawAxis(2)*1;
		turret->SetAngle(angle_change);
		m_turret_angle = angle_change;


		//CLIMBER
		int climberMotor=0;
		if(oi->GetSw5())
			climberMotor=1;
		climber->Set(climberMotor);
		//END CLIMBER


		frc::SmartDashboard::PutNumber("IntakeArm Angle (degrees)", intake->GetArmAngle()*INTAKE_ARM_ROTATIONS_PER_DEGREE);
		frc::SmartDashboard::PutBoolean("Intake Limit Switch", intake->IsIntakeDown());
		frc::SmartDashboard::PutData("Calibrate Arm", new CalibrateArm());
		frc::SmartDashboard::PutBoolean("Intake Closed Loop", intake->IsClosedLoop());
		frc::SmartDashboard::PutNumber("ShooterRPM", shooter->GetRPM());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());


	}

	void TestPeriodic() override {

	}

	void RobotLog()
	{
		//Add all subsystems to log here.
		//drivetrain->Log();

		log->WriteBuffertoFile();
	}

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;

	int shootersetpoint1 = 3000;
	int shootersetpoint2 = 2500;
	float m_armAngle = 0.0;
	float m_turret_angle = 0;


public:

	bool doVisionWithProcessing()
	{
	//this is from remote Camera via networktables
		static int target = 0;
		static double angleOff = 0;
		static double pixPDegree = 0;
		static double pixFCenter = 0;
		const unsigned numberOfParticles = 10;
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
		target = 0;
		if(RcRs[0].Area > 64) target = 1;

			//Publish the sorted 1st two results
			frc::SmartDashboard::PutNumber("angleOff", angleOff);
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
	}

};

START_ROBOT_CLASS(Robot)
