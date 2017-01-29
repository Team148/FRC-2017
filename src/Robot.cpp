#include <memory>
#include <iostream>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "CommandBase.h"
#include "Commands/Auto/Drive.h"
#include "Pathfinder.h"

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
		//frc::Scheduler::GetInstance()->AddCommand(new Drive(120,20));

		//TEST PATHFINDER
		int POINT_LENGTH = 3;

		Waypoint *points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTH);
		Waypoint p1 = { 0, 12, 0 };			// Waypoint @ x=0, y=12, exit angle=45 degrees
		Waypoint p2 = { -12, 12, d2r(-90) };// Waypoint @ x=-12, y= 12, exit angle= -90 radians
		Waypoint p3 = { -12, 0, d2r(-180) };// Waypoint @ x= -12, y= 0, exit angle= 180 radians
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;

		TrajectoryCandidate candidate;

		// Prepare the Trajectory for Generation.
		//
		// Arguments:
		// Fit Function:        FIT_HERMITE_CUBIC or FIT_HERMITE_QUINTIC
		// Sample Count:        PATHFINDER_SAMPLES_HIGH (100 000)
		//                      PATHFINDER_SAMPLES_LOW  (10 000)
		//                      PATHFINDER_SAMPLES_FAST (1 000)
		// Time Step:           0.001 Seconds
		// Max Velocity:        15 m/s
		// Max Acceleration:    10 m/s/s
		// Max Jerk:            60 m/s/s/s
		pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.001, 15.0, 10.0, 60.0, &candidate);
		int length = candidate.length;
		Segment *trajectory = (Segment*)malloc(sizeof(Segment) * length);

		int result = pathfinder_generate(&candidate, trajectory);
		if(result < 0)
			cout <<"error: could not generate a trajectory" << endl;

		Segment *leftTrajectory = (Segment*)malloc(sizeof(Segment) * length);
		Segment *rightTrajectory = (Segment*)malloc(sizeof(Segment) * length);

		double wheelbase_width = 0.6; //in meters

		pathfinder_modify_tank(trajectory, length, leftTrajectory, rightTrajectory, wheelbase_width);

	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		std::cout << "starting TeleopInit" << std::endl;

		//Set Shooter for OpenLoop
		shooter->ConfigureOpenLoop();

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
