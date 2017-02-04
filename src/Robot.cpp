#include <memory>
#include <iostream>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "CommandBase.h"
#include "Commands/Auto/Drive.h"
#include "Commands/Auto/Autonomous.h"

class Robot: public frc::IterativeRobot {
public:

	Drivetrain *drivetrain = 0;
	OI* oi = 0;
	Conveyor* conveyor = 0;
	Intake* intake = 0;
	Shooter* shooter = 0;

	void RobotInit() override {
		std::cout << "starting RobotInit" << std::endl;
		oi = OI::GetInstance();
		drivetrain = Drivetrain::GetInstance();
		conveyor = Conveyor::GetInstance();
		intake = Intake::GetInstance();
		shooter = Shooter::GetInstance();
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

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();

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

		//TESTING Drive command (distance in inches, and velocity in inches per second)
		drivetrain->configClosedLoop();
		frc::Scheduler::GetInstance()->AddCommand(new Autonomous());
//		frc::Scheduler::GetInstance()->AddCommand(new Drive(100,160));
//		frc::Scheduler::GetInstance()->AddCommand(new Drive(100,40));

	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		frc::SmartDashboard::PutNumber("Drive Encoder Velocity: ", drivetrain->GetEncoderVelocity());


	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		std::cout << "starting TeleopInit" << std::endl;

		//Set Shooter for OpenLoop
		shooter->ConfigureOpenLoop();
		drivetrain->configOpenLoop();

		//if (autonomousCommand != nullptr) {
		//	autonomousCommand->Cancel();
		//}

	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();


		//Manual Open Loop Controls
		//Drive control is in Commands/DriveWithJoystick
		ballin=0;
		gear=0;
		shooteron=false;
		conveyorX=0;
		if(oi->opStick->GetRawButton(1)){ ballin=1;}		//Ball Intake
		intake->SetBall(ballin);

		if(oi->opStick->GetRawButton(2)) {gear=1;}		//GearIntake
		if(oi->opStick->GetRawButton(3)) {gear=-1;}		//GearIntake Out
		intake->SetGear(gear);

		intake->SetArm(oi->opStick->GetRawAxis(1));		//Intake Arm


		if(oi->opStick->GetRawButton(4)){conveyorX = 10.0;}	//Run Lower Conveyor (Voltage control)
		conveyor->SetLower(conveyorX);
		conveyor->SetUpper(conveyorX);


		if(oi->opStick->GetRawButton(6)){shooteron=true;}	//Run Shooter

		if(shooteron) { shooter->SetOpenLoop(0.8); }  	//setShooter to ShooterSetpoint
		else {shooter->SetOpenLoop(0); }					//SetShooter 0


		//adjust ShooterRPM up & down
	}

	void TestPeriodic() override {


	}

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;
	float ballin,gear;
	int conveyorX;
	bool shooteron;

	int shootersetpoint = 2800;
};

START_ROBOT_CLASS(Robot)
