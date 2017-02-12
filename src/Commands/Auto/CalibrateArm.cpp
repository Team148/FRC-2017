#include "CalibrateArm.h"

CalibrateArm::CalibrateArm() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void CalibrateArm::Initialize() {
	m_isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void CalibrateArm::Execute() {
	Intake::GetInstance()->SetArm(-.4);
	if(Intake::GetInstance()->IsIntakeDown()) {
		Intake::GetInstance()->ConfigureClosedLoop();
		m_isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CalibrateArm::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void CalibrateArm::End() {
	//Intake::GetInstance()->SetArmAngle(1.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalibrateArm::Interrupted() {

}
