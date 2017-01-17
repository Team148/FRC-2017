#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	//Requires(CommandBase::drivetrain.get());
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {

	//CommandBase::drivetrain->Arcade(CommandBase::oi->drvStick->GetRawAxis(1), CommandBase::oi->drvStick->GetRawAxis(2));
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	//CommandBase::drivetrain->Arcade(0,0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {

}
