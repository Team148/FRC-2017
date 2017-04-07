#include <Commands/Auto/IntakeAutoGearScore.h>
#include <Commands/AutoGearScoreSub.h>
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
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/Auto/AutonRoutines/Blue.h"
#include "Commands/Auto/AutonRoutines/Red.h"
#include "Commands/Auto/SetBallGearUntilBeam.h"
//#include "Vision/VisionAPI.h"
//#include <CameraServer.h>
//#include <Vision/USBCamera.h>


class Robot: public frc::IterativeRobot {
private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> auton_chooser;

	float m_armAngle = 0.0;
	float m_turret_angle = 0.0;
	float angle_change = 0.0;
	bool isAiming = false;
	unsigned int result;

public:
//	std::shared_ptr<NetworkTable> table;
	Drivetrain *drivetrain = 0;
	OI* oi = 0;
	Climber* climber = 0;
	Conveyor* conveyor = 0;
	Intake* intake = 0;
	Shooter* shooter = 0;
	Turret* turret = 0;
	Logger* log = 0;

	void RobotInit() override {
		std::cout << "info: starting RobotInit" << std::endl;
		oi = OI::GetInstance();
		drivetrain = Drivetrain::GetInstance();
		climber = Climber::GetInstance();
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
		//m_turret_angle = 0.0;
		//turret->UpdateNetworkTable();

	}


	void DisabledPeriodic() override {
//		frc::Scheduler::GetInstance()->Run();
//		frc::Scheduler::GetInstance()->RemoveAll();
		//m_turret_angle = 0.0;
		//turret->updatenetworktable();
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
		shooting = oi->GetSw3();
		hopper = oi->GetSw4();


		shooter->ConfigureClosedLoop();
		if(!turret->IsClosedLoop())
		{
			turret->ConfigClosedLoop();
		}
		drivetrain->ResetGyro();
		drivetrain->configClosedLoop();
		drivetrain->SetBrakeMode(true);

		if(!intake->IsClosedLoop())
		{
			if(intake->isSensorPluggedIn() == 1) intake->ConfigureClosedLoop();
			else intake->ConfigureOpenLoop();
		}
		switch(red)
			{
				case RED: // CALL RED(NEW asdf123())
					switch(position)
					{
					case POSITION_BOILER:
						if(gears == 1 && shooting == 0 && hopper == 0) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR));
						else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_TWO_GEAR));
						else if(gears == 1 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR_HOPPER_SHOOT));
						else if(gears == 1 && shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_GEAR_SHOOT));
						else if(gears == 0 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(BOILER_HOPPER_SHOOT));
					break;
					case POSITION_CENTER:
						if(gears == 1 && !shooting) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_GEAR));
						else if(gears == 1 && shooting) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_GEAR_SHOOT));
						else if (gears == 2 && gear_noscore == true && !shooting) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_TWO_GEAR_NOSCORE));
						else if (gears == 2 && gear_noscore == true  && shooting) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_TWO_GEAR_NOSCORE_SHOOT));
						else if(gears == 2 && gear_noscore == false) frc::Scheduler::GetInstance()->AddCommand(new Red(CENTER_TWO_GEAR));
					break;
					case POSITION_RETRIEVAL:
						if(gears == 1 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(RETRIEVAL_GEAR));
						else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(RETRIEVAL_TWOGEAR));
						else if(gears == 1 && shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Red(RETRIEVAL_GEAR_SHOOT));

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
						else if(gears == 1 && shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_SHOOT));
						else if(gears == 0 && shooting && hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_HOPPER_SHOOT));
					break;
					case POSITION_CENTER:
						if(gears == 1 && !shooting) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_GEAR));
						else if(gears == 1 && shooting) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_GEAR_SHOOT));
						else if (gears == 2 && gear_noscore == true && !shooting) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_TWO_GEAR_NOSCORE));
						else if (gears == 2 && gear_noscore == true  && shooting) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_TWO_GEAR_NOSCORE_SHOOT));
						else if(gears == 2 && gear_noscore == false) frc::Scheduler::GetInstance()->AddCommand(new Blue(CENTER_TWO_GEAR));
					break;
					case POSITION_RETRIEVAL:
						if(gears == 1 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(RETRIEVAL_GEAR));
						else if(gears == 2 && !shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(RETRIEVAL_TWOGEAR));
						else if(gears == 1 && shooting && !hopper) frc::Scheduler::GetInstance()->AddCommand(new Blue(RETRIEVAL_GEAR_SHOOT));

					break;
					}
				break;
			}




		//frc::Scheduler::GetInstance()->AddCommand(new Center1Gear());
		//frc::Scheduler::GetInstance()->AddCommand(new Autonomous());
		m_turret_angle = 0.0;

//		if(!intake->IsClosedLoop())
//		{
//			if(intake->isSensorPluggedIn() == 1)
//			else intake->ConfigureOpenLoop();
//		}
		//turret->UpdateNetworkTable();
		//frc::Scheduler::GetInstance()->AddCommand(new Blue(3));
		//frc::Scheduler::GetInstance()->AddCommand(new Autonomous(red, position, gears, shooting, hopper));
		//frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_HOPPER_SHOOT));
		//frc::Scheduler::GetInstance()->AddCommand(new SetBallGearUntilBeam());


	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		//turret->UpdateNetworkTable();
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
		if(!turret->IsClosedLoop())
		{
			turret->ConfigClosedLoop();
		}
		//m_turret_angle = 0.0;

		//intake->ResetArm(0.0);

		//turret->updatenetworktable();

//		if (autonomousCommand != nullptr) {
//			autonomousCommand->Cancel();
//		}
		if(!intake->IsClosedLoop())
		{
			if(intake->isSensorPluggedIn() == 1) intake->ConfigureClosedLoop();
			else intake->ConfigureOpenLoop();
		}
		//intake->ConfigureOpenLoop();
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
		static float cur_armPosition = 0.0;
		static bool shooterReady = false;
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



//		if(oi->opStick->GetRawButton(1)) //Ball Intake
//		{
//			ballIntake = 1.0; // intake
//		}
//		if(oi->opStick->GetRawButton(2))
//		{
//			ballIntake = -1.0; // outake
//		}



		if(oi->opStick->GetRawButton(2)) //GearIntake OUT
		{
			gearIntake = 1.0;
		}
		static bool autoPickup = false;
		static float st_time = 0.0;
		static int flashCount = 0;
		if(oi->opStick->GetRawButton(3)) //GearIntake IN
		{
			gearIntake = -1.0;
			if(intake->IsBeamBroke())
			{
				autoPickup = true;

			}
		}
		if(autoPickup == true)
		{
			if(st_time - Timer::GetFPGATimestamp() <= 0.10 && flashCount < 5)
			{
				ringlightOn = 1;
			}
			else
			{
				st_time = Timer::GetFPGATimestamp();
				flashCount++;
				ringlightOn = 0;
			}
		}

		//AGITATOR AND SHOOTER FIRE
		if(oi->opStick->GetRawButton(5))
		{
			kicker = CONVEYER_KICKER_VOLTAGE;

			//ballIntake = 0.25;

		}	//Run Agitator (Voltage control)
		if(oi->opStick->GetRawButton(6))
		{
			agitator = CONVEYER_AGITATOR_VOLTAGE;
			kicker = CONVEYER_KICKER_VOLTAGE;
			//ballIntake = 0.25;
		}	//Run Agitator and fire (Voltage control)




		//CLOSED LOOP ARM CODE
		//Shoulder Buttons
		static bool goingDown = false;
		static bool goingUp = false;
		static bool enableGearTolerance_down = false;
		static bool enableGearTolerance_up = false;
		static bool gearWhileUp = false;
		cur_armPosition = intake->GetArmAngle();
static bool autoArmUp = false;
		if(intake->IsClosedLoop()) {
			if(oi->drvStick->GetRawButton(6)) // AUTOSCORE SETTER
			{
				autoArmUp = true;
				enableGearTolerance_up = false;
				enableGearTolerance_down = false;
				m_armAngle = INTAKE_ARM_GEAR_POSITION;
				gearIntake = 0.05;
			}
			if(autoArmUp && !oi->drvStick->GetRawButton(6))
			{
				m_armAngle = INTAKE_ARM_POSITION_UP;
				autoArmUp = false;
			}
			if(oi->opStick->GetRawButton(1)){
				//intake->SetArmAngle(0.0); //down
				m_armAngle = INTAKE_ARM_POSITION_DOWN;
				goingUp = false;
				goingDown = true;
				enableGearTolerance_down = false;
				enableGearTolerance_up = false;
				gearWhileUp = false;
			}
			if(goingDown)
			{
				if(intake->GetArmAngle() <= (INTAKE_ARM_POSITION_DOWN*0.95))
				{
					enableGearTolerance_down = true;
					enableGearTolerance_up = false;
					goingDown = false;
				}
			}
			if(enableGearTolerance_down)
			{
				m_armAngle = cur_armPosition;
				intake->setPID(0,0,0);
				if(cur_armPosition >= INTAKE_ARM_POSITION_DOWN*0.94)
				{
					intake->setPID(INTAKE_ARM_POSITION_P,INTAKE_ARM_POSITION_I,INTAKE_ARM_POSITION_D);
					m_armAngle = INTAKE_ARM_POSITION_DOWN;
				}
			}
			else if(!enableGearTolerance_up && !enableGearTolerance_down)
			{
				intake->setPID(INTAKE_ARM_POSITION_P,INTAKE_ARM_POSITION_I,INTAKE_ARM_POSITION_D);
			}
			if(oi->opStick->GetRawButton(4)) {
				goingDown = false;
				goingUp = true;
				enableGearTolerance_down = false;
				enableGearTolerance_up = false;
				//intake->SetArmAngle(1.12); //up
				m_armAngle = INTAKE_ARM_POSITION_UP;
				gearWhileUp = true;
			}
			if(goingUp)
			{
				gearIntake = -1.0;
				if(cur_armPosition >= INTAKE_ARM_POSITION_UP-0.06)
				{
					enableGearTolerance_up = true;
					enableGearTolerance_down = false;
					goingUp = false;
				}
			}
			if(enableGearTolerance_up)
			{
				m_armAngle = cur_armPosition;
				intake->setPID(0,0,0);
				if(cur_armPosition <= INTAKE_ARM_POSITION_UP-0.06)
					{
						intake->setPID(INTAKE_ARM_POSITION_P,INTAKE_ARM_POSITION_I,INTAKE_ARM_POSITION_D);
						m_armAngle = INTAKE_ARM_POSITION_UP;
					}
			}
			else if(!enableGearTolerance_up && !enableGearTolerance_down)
			{
				intake->setPID(INTAKE_ARM_POSITION_P,INTAKE_ARM_POSITION_I,INTAKE_ARM_POSITION_D);
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
//			if(oi->drvStick->GetRawAxis(3) > 0.2)
//				m_armAngle = (INTAKE_ARM_POSITION_UP/2) + oi->drvStick->GetRawAxis(3)*(INTAKE_ARM_POSITION_UP/2);

			if(m_armAngle <= INTAKE_ARM_POSITION_DOWN) m_armAngle = INTAKE_ARM_POSITION_DOWN; // Hard Stop stall Safety (down)
			if(m_armAngle >= INTAKE_ARM_POSITION_UP) m_armAngle = INTAKE_ARM_POSITION_UP; // Hard Stop stall Safety (up)

			intake->SetArmAngle(m_armAngle);
		}
		else {  //OPEN LOOP INTAKE

				if(oi->opStick->GetRawButton(1)){
					//down
					armMotor = -(INTAKE_ARM_OPEN_LOOP_SPEED);
				}
				if(oi->opStick->GetRawButton(4)) {
					//up
					gearIntake = -1.0;
					armMotor = INTAKE_ARM_OPEN_LOOP_SPEED*0.75;
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
		if(oi->opStick->GetRawButton(7))	//shooter off
		{
			shooterRpm = 0;
		}
		if(shooter->GetRPM() + 100  >= shooterRpm) shooterReady = true;
		else shooterReady = false;

		//AUTO SCORE
//		if(oi->drvStick->GetRawButton(3)) {
//			//m_armAngle = INTAKE_ARM_GEAR_POSITION;
//			frc::Scheduler::GetInstance()->AddCommand(new AutoGearScoreSub());
//		}


		if(shooterRpm < 0) // prevents shooter from being set to a negative rpm
			shooterRpm = 0;
		shooter->SetRPM(shooterRpm);
		frc::SmartDashboard::PutNumber("commandedRPM", shooterRpm);
		//END CLOSEDLOOP SHOOTER





		//END MANUAL FLASHLIGHT CONTROL


		//TURRET


		if(oi->opStick->GetRawButton(8)) //Home Turret
		{
			if(oi->GetSw1())
			{
				m_turret_angle = SHOOTING_POSITION_RED;
				angle_change = SHOOTING_POSITION_RED;
			}
			if(!oi->GetSw1())
			{
				m_turret_angle = SHOOTING_POSITION_BLUE;
				angle_change = SHOOTING_POSITION_BLUE;
			}
//			m_turret_angle = 0.0;
//			angle_change = 0.0;
		}

		//turret->updatenetworktable();
		isAiming = false;
		if(oi->opStick->GetRawButton(10)) {	//USE Gyro then VISION to steer turret
			flashlightOn = false;
			ringlightOn = true;
			isAiming = true;
			turret->TargetBoiler(true);
			m_turret_angle = turret->GetBigAngle();
		} else {
			float turret_joy_in;
			float turret_fastjoy_in;
			if(!oi->GetSw5())
			{
				turret_fastjoy_in = oi->opStick->GetRawAxis(0);
				turret_joy_in = oi->opStick->GetRawAxis(4);
			}
			else
			{
				turret_fastjoy_in = 0.0;
				turret_joy_in = 0.0;
			}

			if(abs(turret_joy_in) < TURRET_JOYSTICK_DEADBAND)
				turret_joy_in = 0;

			if(abs(turret_fastjoy_in) < TURRET_JOYSTICK_DEADBAND)
				turret_fastjoy_in = 0;

			angle_change = m_turret_angle + (turret_joy_in * TURRET_SPEED) + (turret_fastjoy_in* TURRET_SPEED*3);
			m_turret_angle = angle_change;
			turret->SetBigAngle(angle_change);  //moved outside of routine
			//turret->SetBigAngle(turret_joy_in*22);
			isAiming = false;
			//turret->TargetBoiler(false);

		}

		double _angle = turret->GetBigAngle();
		frc::SmartDashboard::PutNumber("Turret Angle", _angle);

		//Manual Flashlight control

		//manual ringlight control
		if(oi->opStick->GetRawAxis(2) >= 0.1) {
				flashlightOn = true;
		}

		if(oi->opStick->GetRawAxis(3) >= 0.1)
		{
			ringlightOn = true;
		}


		//CLIMBER
		if(oi->GetSw5())
		{
			climberMotor =	abs(oi->opStick->GetRawAxis(1))*-12.0;
		}
		else
		{
			climberMotor = 0.0;
		}



		climber->Set(climberMotor);
		conveyor->SetAgitator(agitator);
		conveyor->SetKicker(kicker);
		//END AGITATOR AND FIRE
		intake->SetBall(ballIntake);
		shooter->SetRingLightOn(ringlightOn);
		shooter->SetFlashlightOn(flashlightOn);
		intake->SetGear(gearIntake);


		//END CLIMBER


		SmartDashUpdate();
		SmartDashboard::PutBoolean("SHOOTER_READY", shooterReady);
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
		//frc::SmartDashboard::PutBoolean("Intake Limit Switch", intake->IsIntakeDown());
		//frc::SmartDashboard::PutData("Calibrate Arm", new CalibrateArm(false));
		frc::SmartDashboard::PutBoolean("Intake Closed Loop", intake->IsClosedLoop());
		frc::SmartDashboard::PutNumber("ShooterRPM", shooter->GetRPM());
		frc::SmartDashboard::PutNumber("Shooter Current", shooter->GetCurrent());
		frc::SmartDashboard::PutNumber("Shooter Voltage", shooter->GetVoltage());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
		frc::SmartDashboard::PutBoolean("Beam Break", intake->IsBeamBroke());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
		frc::SmartDashboard::PutNumber("Vision Offset", turret->GetVisionOffset());
		frc::SmartDashboard::PutNumber("Intake Current", drivetrain->m_pdp->GetCurrent(5));


		frc::SmartDashboard::PutNumber("SW1", oi->GetSw1());
		frc::SmartDashboard::PutNumber("SW2", oi->GetSw2());
		frc::SmartDashboard::PutNumber("SW3", oi->GetSw3());
		frc::SmartDashboard::PutNumber("SW4", oi->GetSw4());
		frc::SmartDashboard::PutNumber("SW5", oi->GetSw5());
		frc::SmartDashboard::PutNumber("SW_A", oi->GetSelectorA());
		frc::SmartDashboard::PutNumber("SW_B", oi->GetSelectorB());



	}

};

START_ROBOT_CLASS(Robot)
