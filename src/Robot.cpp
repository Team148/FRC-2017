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
#include "Commands/Auto/SetBallGearUntilBeam.h"
#include "Commands/AutoGearScore.h"
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
	float _angle;

public:

	Drivetrain *drivetrain = 0;
	OI* oi = 0;
	Conveyor* conveyor = 0;
	Intake* intake = 0;
	Shooter* shooter = 0;
	Turret* turret = 0;
	Logger* log = 0;

	void RobotInit() override {
		std::cout << "info: starting RobotInit" << std::endl;
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
		turret->UpdateNetworkTable();
	}


	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		m_turret_angle = 0.0;
		turret->UpdateNetworkTable();
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
		//}
		log->Start();
		drivetrain->configClosedLoop();
		drivetrain->ResetGyro();
		drivetrain->SetBrakeMode(true);
		//frc::Scheduler::GetInstance()->AddCommand(new Center1Gear());
		//frc::Scheduler::GetInstance()->AddCommand(new Autonomous());
		m_turret_angle = 0.0;

		frc::Scheduler::GetInstance()->AddCommand(new Blue(BOILER_GEAR_HOPPER_SHOOT));
		//frc::Scheduler::GetInstance()->AddCommand(new SetBallGearUntilBeam());


	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		turret->UpdateNetworkTable();
		SmartDashUpdate();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		std::cout << "starting TeleopInit" << std::endl;
		//Set Shooter for OpenLoop
		shooter->ConfigureClosedLoop();
		drivetrain->configOpenLoop();
		drivetrain->SetBrakeMode(false);
		turret->ConfigClosedLoop();
		m_turret_angle = 0.0;

		if(!intake->IsClosedLoop())
			frc::Scheduler::GetInstance()->AddCommand(new CalibrateArm());

//		if (autonomousCommand != nullptr) {
//			autonomousCommand->Cancel();
//		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		turret->UpdateNetworkTable();

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
		float current_angle = 0.0;



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
				m_armAngle = 0.0;
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

			if(m_armAngle <= 0.0) m_armAngle = 0.0; // Hard Stop stall Safety (down)
			if(m_armAngle >= 1.14) m_armAngle = 1.14; // Hard Stop stall Safety (up)

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
		intake->SetArm(armMotor);
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
		if(shooterRpm != 0)	//If shooter is on, turn the flashlight ON
		{
			flashlightOn = true;
		}

		//AUTO SCORE
		if(oi->drvStick->GetRawButton(3)) {
			m_armAngle = INTAKE_ARM_POSITION_UP*0.55;
			frc::Scheduler::GetInstance()->AddCommand(new AutoGearScore());

		}


		if(shooterRpm < 0) // prevents shooter from being set to a negative rpm
			shooterRpm = 0;
		shooter->SetRPM(shooterRpm);
		frc::SmartDashboard::PutNumber("commandedRPM", shooterRpm);
		//END CLOSEDLOOP SHOOTER

		//Manual Flashlight control
		if(oi->drvStick->GetRawButton(1)) {
			flashlightOn = true;
		}


		shooter->SetFlashlightOn(flashlightOn);

		//END MANUAL FLASHLIGHT CONTROL


		//TURRET
		float turret_joy_in = oi->opStick->GetRawAxis(4);
		if(abs(turret_joy_in) < TURRET_JOYSTICK_DEADBAND)   //Adds deadband to joystick
			turret_joy_in = 0;
		float angle_change = m_turret_angle - turret_joy_in * TURRET_SPEED;
		m_turret_angle = angle_change;

		if(oi->opStick->GetRawButton(8)) { //Home Turret
			m_turret_angle = 0.0;
			angle_change = 0.0;
		}


		if(oi->opStick->GetRawButton(10)) {	//USE Gyro then VISION to steer turret
			current_angle = Drivetrain::GetInstance()->GetAngle();
			turret->SetBigAngle(current_angle); //turret follows the gyro angle degs

			//wait here to get to angle
			turret->GetVisionOffset();
//			turret->SetAngle(_angle);
			ringlightOn = true;
		} else turret->SetAngle(angle_change);  //this call set motor small gear angle on turret



		//manual ringlight control
		if(oi->drvStick->GetRawButton(2)) {
				ringlightOn = true;
		}
		shooter->SetRingLightOn(ringlightOn);



		//CLIMBER
		if(oi->GetSw5())
			climberMotor =- 12.0;
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
		frc::SmartDashboard::PutData("Calibrate Arm", new CalibrateArm());
		frc::SmartDashboard::PutBoolean("Intake Closed Loop", intake->IsClosedLoop());
		frc::SmartDashboard::PutNumber("ShooterRPM", -shooter->GetRPM());
		frc::SmartDashboard::PutNumber("Shooter Current", shooter->GetCurrent());
		frc::SmartDashboard::PutNumber("Shooter Voltage", -shooter->GetVoltage());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
		frc::SmartDashboard::PutBoolean("Beam Break", intake->IsBeamBroke());
		frc::SmartDashboard::PutNumber("Gyro Angle", drivetrain->GetAngle());
		frc::SmartDashboard::PutNumber("Turret Angle", turret->GetBigAngle());

	}

};

START_ROBOT_CLASS(Robot)
