#include "ShooterUpdate.h"

ShooterUpdate::ShooterUpdate() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Shooter::GetInstance());
	//m_speed = speed;
}

// Called just before this Command runs the first time
void ShooterUpdate::Initialize() {
	//Shooter::GetInstance()->cur_speed += m_speed;
	std::cout << "ShooterUpdate Init" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void ShooterUpdate::Execute() {
	std::cout << "ShooterUpdate Execute " << Shooter::GetInstance()->cur_speed << std::endl;
	Shooter::GetInstance()->SetClosedLoop(Shooter::GetInstance()->cur_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterUpdate::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterUpdate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterUpdate::Interrupted() {

}
