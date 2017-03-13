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
#include "Commands/Auto/AutonRoutines/Autonomous.h"
#include "commands/Auto/Center1Gear.h"
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/Auto/AutonRoutines/Blue.h"
#include "Commands/Auto/AutonRoutines/Red.h"

#include "Commands/Auto/SetBallGearUntilBeam.h"
#include "Commands/AutoGearScore.h"
//#include "Vision/VisionAPI.h"
//#include <CameraServer.h>
//#include <Vision/USBCamera.h>



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



unsigned int doVisionWithProcessing(float &angle_change, float &m_turret_angle);

// Sort Container by Area function
bool sortByArea(const RemoteContourReport &lhs, const RemoteContourReport &rhs) { return lhs.Area > rhs.Area; }


class Robot: public frc::IterativeRobot {
private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> auton_chooser;

	float m_armAngle = 0.0;
	float m_turret_angle = 0.0;
	float angle_change = 0.0;
	unsigned int result;


//	unsigned int doVisionWithProcessing(float angle, float &m_turret_angle);

public:
	std::shared_ptr<NetworkTable> table;
	Drivetrain *drivetrain = 0;
	OI* oi = 0;
	Conveyor* conveyor = 0;
	Intake* intake = 0;
	Shooter* shooter = 0;
	Turret* turret = 0;
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
		log = new Logger();
		
		//AUTON Modes
//		auton_chooser.AddDefault("Testing Auton", new Autonomous());
//		auton_chooser.AddObject("Center 1 Gear", new Center1Gear());
		frc::SmartDashboard::PutData("Auto Modes", &auton_chooser);

	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {
		m_turret_angle = 0.0;
		result = doVisionWithProcessing(angle_change, m_turret_angle);
	}


	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		frc::Scheduler::GetInstance()->RemoveAll();
		m_turret_angle = 0.0;
		result = doVisionWithProcessing(angle_change, m_turret_angle);
		SmartDashUpdate();
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

		//autonomousCommand.reset(auton_chooser.GetSelected());

		//if (autonomousCommand.get() != nullptr) {
		//	autonomousCommand->Start();
		frc::Scheduler::GetInstance()->RemoveAll();
		log->Start();
		static int red = 0;
		static bool shooting = false;
		static bool hopper = false;
		static int gears = 0;
		static int position = 0;
		static int gear_noscore = false;

		red = oi->GetSw1();
		position = oi->GetSelectorB();
		gears = oi->GetSelectorA();
		gear_noscore = oi->GetSw2();
		//shooting = oi->GetSw2();
		//hopper = oi->GetSw3();

		switch(red)
			{
				case RED: // CALL RED(NEW asdf123())
					switch(position)
					{
						case POSITION_BOILER:
							if(gears == 1 && shooting == 0 && hopper == 0) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR));
							else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_TWO_GEAR));
							else if(gears == 1 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_GEAR_HOPPER_SHOOT));
							else if(gears == 0 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Red (BOILER_HOPPER_SHOOT));
						break;
						case POSITION_CENTER:
							if(gears == 1 ) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_GEAR));
							else if (gears == 2 && gear_noscore == true) frc::Scheduler::GetInstance()->AddCommand(new Red (CENTER_TWO_GEAR_NOSCORE));
							else if(gears == 2 && gear_noscore == false) frc::Scheduler::GetInstance()->AddCommand(new Red (CENTER_TWO_GEAR));
						break;
						case POSITION_RETRIEVAL:
							if(gears == 1 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(RETRIEVAL_GEAR));
							else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red (RETRIEVAL_TWOGEAR));
						break;
					}
				break;

				case BLUE: // CALL BLUE(NEW asdf123())
					switch(position)
					{
					case POSITION_BOILER:
						if(gears == 1 && shooting == 0 && hopper == 0) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR));
						else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_TWO_GEAR));
						else if(gears == 1 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_HOPPER_SHOOT));
						else if(gears == 0 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_HOPPER_SHOOT));
					break;
					case POSITION_CENTER:
						if(gears == 1) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_GEAR));
						else if (gears == 2 && gear_noscore == true) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_TWO_GEAR_NOSCORE));
						else if(gears == 2 && gear_noscore == false) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_TWO_GEAR));
					break;
					case POSITION_RETRIEVAL:
						if(gears == 1 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(RETRIEVAL_GEAR));
						else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(RETRIEVAL_TWOGEAR));
					break;
					}
				break;
			}



		drivetrain->configClosedLoop();
		drivetrain->SetBrakeMode(true);
		//frc::Scheduler::GetInstance()->AddCommand(new Center1Gear());
		//frc::Scheduler::GetInstance()->AddCommand(new Autonomous());
		m_turret_angle = 0.0;

		result = doVisionWithProcessing(angle_change, m_turret_angle);
		//frc::Scheduler::GetInstance()->AddCommand(new Blue(3));
		//frc::Scheduler::GetInstance()->AddCommand(new Autonomous(red, position, gears, shooting, hopper));
		//frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_HOPPER_SHOOT));
		//frc::Scheduler::GetInstance()->AddCommand(new SetBallGearUntilBeam());


	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		//result = doVisionWithProcessing(angle_change, m_turret_angle);
		SmartDashUpdate();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		frc::Scheduler::GetInstance()->RemoveAll();
		std::cout << "starting TeleopInit" << std::endl;


		shooter->ConfigureClosedLoop();
		drivetrain->configOpenLoop();
		drivetrain->SetBrakeMode(false);
		turret->ConfigClosedLoop();
		m_turret_angle = 0.0;


		result = doVisionWithProcessing(angle_change, m_turret_angle);

//		if (autonomousCommand != nullptr) {
//			autonomousCommand->Cancel();
//		}
		if(!intake->IsClosedLoop())
			frc::Scheduler::GetInstance()->AddCommand(new CalibrateArm(false));
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();

		static float ballIntake = 0.0;
		static float gearIntake = 0.0;
		static float armMotor = 0.0;
		static float agitator = 0.0;
		static float kicker = 0.0;
		static float climberMotor = 0.0;
		static int shooterRpm = 0;
		static bool armIncPressed = false;
		static bool armBtnSafe = false;
		static bool flashlightOn = false;
		static bool ringlightOn = false;
		static float temp_angle = 0.0;
//		float current_angle = 0.0;



		//Manual Open Loop Controls
		//Drive control is in Commands/DriveWithJoystick
		ballIntake = 0.0;
		gearIntake = 0.0;
		agitator = 0.0;
		kicker = 0.0;
		armMotor = 0.0;
		climberMotor = 0.0;
		flashlightOn = false;
		ringlightOn = false;



		if(oi->opStick->GetRawButton(1)) //Ball Intake
		{
			ballIntake = 1.0; // intake
		}
		if(oi->opStick->GetRawButton(2))
		{
			ballIntake = -1.0; // outake
		}



		if(oi->opStick->GetRawButton(3)) //GearIntake In
		{
			gearIntake = 1.0;
		}
		if(oi->opStick->GetRawButton(4)) //GearIntake Out
		{
			gearIntake = -1.0;
		}
		intake->SetGear(gearIntake);

		//AGITATOR AND SHOOTER FIRE
		if(oi->opStick->GetRawButton(5))
		{
			agitator = -CONVEYER_AGITATOR_VOLTAGE;
			ballIntake = 0.25;

		}	//Run Agitator (Voltage control)
		if(oi->opStick->GetRawButton(6))
		{
			agitator = -CONVEYER_AGITATOR_VOLTAGE;
			kicker = CONVEYER_KICKER_VOLTAGE;
			ballIntake = 0.25;
		}	//Run Agitator and fire (Voltage control)

		conveyor->SetAgitator(agitator);
		conveyor->SetKicker(kicker);
		//END AGITATOR AND FIRE
		intake->SetBall(ballIntake);


		//CLOSED LOOP ARM CODE
		//Shoulder Buttons


		if(intake->IsClosedLoop()) {
			if(oi->drvStick->GetRawButton(5)){
				//intake->SetArmAngle(0.0); //down
				m_armAngle = INTAKE_ARM_POSITION_DOWN;
			}
			if(oi->drvStick->GetRawButton(6)) {
				//intake->SetArmAngle(1.12); //up
				m_armAngle = INTAKE_ARM_POSITION_UP;
			}

			//increment Arm Up/Down
			//if(oi->drvStick->GetRawButton(1)) {
			//	m_armAngle -= 0.025;
			//}

//			if(oi->drvStick->GetRawButton(4)) { // Increment Arm position up, when btn released set to zero
//				m_armAngle += 0.025;
//				armIncPressed = true;
//				armBtnSafe = false;
//			}
//			else armBtnSafe = true;
//
//			if(armIncPressed && armBtnSafe)
//			{
//				m_armAngle = 0.0;
//				armIncPressed = false;
//			} // ---

			//right trigger arm control (absolute position
			if(oi->drvStick->GetRawAxis(3) > 0.2)
				m_armAngle = (INTAKE_ARM_POSITION_UP/2) + oi->drvStick->GetRawAxis(3)*(INTAKE_ARM_POSITION_UP/2);

			if(m_armAngle <= INTAKE_ARM_POSITION_DOWN) m_armAngle = INTAKE_ARM_POSITION_DOWN; // Hard Stop stall Safety (down)
			if(m_armAngle >= INTAKE_ARM_POSITION_UP) m_armAngle = INTAKE_ARM_POSITION_UP; // Hard Stop stall Safety (up)

			intake->SetArmAngle(m_armAngle);
		}
		else {  //OPEN LOOP INTAKE

				if(oi->drvStick->GetRawButton(6)){
					//down
					armMotor = -(INTAKE_ARM_OPEN_LOOP_SPEED);
				}
				if(oi->drvStick->GetRawButton(5)) {
					//up
					armMotor = INTAKE_ARM_OPEN_LOOP_SPEED;
				}
				if(!intake->IsCalibrating()){
					intake->SetArm(armMotor);
				}
		}
		//END INTAKE ARM



		//OPEN LOOP SHOOTER
//		if(oi->opStick->GetRawButton(6)){shooteron=true;}	//Run Shooter
//
//		if(shooteron) { shooter->SetOpenLoop(0.8); }  		//setShooter to ShooterSetpoint
//		else {shooter->SetOpenLoop(0); }					//SetShooter 0


		//CLOSED LOOP SHOOTER
		if(oi->opStick->GetPOV() == 180) //RPM adjust up
		{
			shooterRpm -= 10;
		}

		if(oi->opStick->GetPOV() == 0) //RPM adjust down
		{
			shooterRpm += 10;
		}

		if(oi->opStick->GetPOV() == 270)
		{
			shooterRpm = SHOOTER_SET_POINT_A;
		}
		if(oi->opStick->GetPOV() == 90)
		{
			shooterRpm = SHOOTER_SET_POINT_B;
		}
		if(oi->opStick->GetRawButton(7))	//Turret off
		{
			shooterRpm = 0;
		}


		//AUTO SCORE
		if(oi->drvStick->GetRawButton(3)) {
			m_armAngle = INTAKE_ARM_GEAR_POSITION;
			frc::Scheduler::GetInstance()->AddCommand(new AutoGearScore());
		}


		if(shooterRpm < 0) // prevents shooter from being set to a negative rpm
			shooterRpm = 0;
		shooter->SetRPM(shooterRpm);
		frc::SmartDashboard::PutNumber("commandedRPM", shooterRpm);
		//END CLOSEDLOOP SHOOTER




		shooter->SetFlashlightOn(flashlightOn);

		//END MANUAL FLASHLIGHT CONTROL


		//TURRET


		if(oi->opStick->GetRawButton(8)) //Home Turret
		{
			m_turret_angle = 0.0;
			angle_change = 0.0;
		}


		if(oi->opStick->GetRawButton(10)) {	//USE Gyro then VISION to steer turret
//			current_angle = Drivetrain::GetInstance()->GetAngle();
//			turret->SetBigAngle(current_angle); //turret follows the gyro angle degs
//			_angle = turret->GetBigAngle();
//			frc::SmartDashboard::PutNumber("Turret Angle", _angle);
			//wait here to get to angle
			result = doVisionWithProcessing(angle_change, m_turret_angle);
			flashlightOn = false;
			ringlightOn = true;

		} else {
			float turret_joy_in = oi->opStick->GetRawAxis(4);
			if(abs(turret_joy_in) < TURRET_JOYSTICK_DEADBAND)
			turret_joy_in = 0;
			angle_change = m_turret_angle - turret_joy_in * TURRET_SPEED;
		}
		turret->SetAngle(angle_change);  //moved outside of routine
		m_turret_angle = angle_change;


		//Manual Flashlight control
		if(oi->drvStick->GetRawButton(1)) {
			flashlightOn = true;
		}
		//manual ringlight control
		if(oi->drvStick->GetRawButton(2)) {
				ringlightOn = true;
		}
		shooter->SetRingLightOn(ringlightOn);



		//CLIMBER
		if(oi->GetSw5())
		{
			climberMotor =	-oi->opStick->GetRawAxis(1)*12.0;
		}
		if(climberMotor >= 0.0) climberMotor = 0.0;

		conveyor->SetClimber(climberMotor);
		//END CLIMBER


		SmartDashUpdate();
	}

	void TestPeriodic() override {

	}

	void RobotLog() {
		//Add all subsystems to log here.
		//drivetrain->Log();

		log->WriteBuffertoFile();
	}



	void SmartDashUpdate() {
		frc::SmartDashboard::PutNumber("IntakeArm Angle (degrees)", intake->GetArmAngle()*INTAKE_ARM_ROTATIONS_PER_DEGREE);
		frc::SmartDashboard::PutBoolean("Intake Limit Switch", intake->IsIntakeDown());
		frc::SmartDashboard::PutData("Calibrate Arm", new CalibrateArm(false));
		frc::SmartDashboard::PutBoolean("Intake Closed Loop", intake->IsClosedLoop());
		frc::SmartDashboard::PutNumber("ShooterRPM", -shooter->GetRPM());
		frc::SmartDashboard::PutNumber("Shooter Current", shooter->GetCurrent());
		frc::SmartDashboard::PutNumber("Shooter Voltage", -shooter->GetVoltage());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
		frc::SmartDashboard::PutBoolean("Beam Break", intake->IsBeamBroke());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());

		frc::SmartDashboard::PutNumber("SW1", oi->GetSw1());
		frc::SmartDashboard::PutNumber("SW2", oi->GetSw2());
		frc::SmartDashboard::PutNumber("SW3", oi->GetSw3());
		frc::SmartDashboard::PutNumber("SW4", oi->GetSw4());
		frc::SmartDashboard::PutNumber("SW5", oi->GetSw5());
		frc::SmartDashboard::PutNumber("SW_A", oi->GetSelectorA());
		frc::SmartDashboard::PutNumber("SW_B", oi->GetSelectorB());



	}

	unsigned int doVisionWithProcessing(float &angle_change, float &m_turret_angle) {
	//this is from remote Camera via networktables
		static int target = 0;
		static double last_angle = 0;
		static double mult = 0.0002;
		double pixel_offset = 0;
//		static double angleOff = 0;
//		static double pixPDegree = 0;
//		static double pixFCenter = 0;
		const unsigned numberOfParticles = 1000;
//		double VIEW_ANGLE = 60;  //HD3000 640x480

		std::vector<double> arr1 = table->GetNumberArray("area", llvm::ArrayRef<double>());
		std::vector<double> arr2 = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
		std::vector<double> arr3 = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
		std::vector<double> arr4 = table->GetNumberArray("height", llvm::ArrayRef<double>());
		std::vector<double> arr5 = table->GetNumberArray("width", llvm::ArrayRef<double>());

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

			std::sort(RcRs.begin(), RcRs.end(), sortByArea); //Sort the result by Area of target

			//only looking at top two biggest areas.  May need to sort deeper if false targets
			if (target == 6) target = 0;
			if((RcRs[0].Area > 64) && (abs(RcRs[0].Width - RcRs[1].Width) < 7) && (target == 0) ) {
			//Here if we have a valid target
			//Our GRIP processing resizes the Image to 640W(x) x 480H(y).  So center of FOV is (x,y) = (160,120).
			//Our target bounding boxes are (Top, Bottom, Left, Right) = (CenterY+Height/2, CenterY-Height/2,...
			//CenterX-Width/2, CenterX+Width/2) where these are target cooridinates.
			//We can try just taking the FOV centerX - target CenterX and use that offset to control speed
			//and direction of the turret.  Max delta is 160.  1/160 is 0.00625
			pixel_offset = (320.0 - RcRs[0].CenterX);
			if(fabs(pixel_offset) < 5) mult = 0.0003;
			angle_change = m_turret_angle - pixel_offset * -mult;  //.000625 may need to invert this range -0.1 to 0.1


//below not working probably have to slow snapshot more
//			angle_change = ((320.0 - RcRs[0].CenterX) * 0.095);  // +/-30deg
//			turret->SetBigAngle(angle_change);

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
		return target;
	}

};

START_ROBOT_CLASS(Robot)
