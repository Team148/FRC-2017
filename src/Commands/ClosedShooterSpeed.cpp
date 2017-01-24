#include "ClosedShooterSpeed.h"

ClosedShooterSpeed::ClosedShooterSpeed(int adj_speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Shooter::GetInstance());
	m_speed = adj_speed;

}

// Called just before this Command runs the first time
void ClosedShooterSpeed::Initialize() {

	Shooter::GetInstance()->ConfigureClosedLoop();
	static int setspeed;
	setspeed += m_speed;


	frc::SmartDashboard::PutNumber("Talon Speed: ", setspeed);

	Shooter::GetInstance()->SetClosedLoop(setspeed);


}

// Called repeatedly when this Command is scheduled to run
void ClosedShooterSpeed::Execute() {


}

// Make this return true when this Command no longer needs to run execute()
bool ClosedShooterSpeed::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClosedShooterSpeed::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClosedShooterSpeed::Interrupted() {

}
