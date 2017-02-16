#include "CalibrateArm.h"

CalibrateArm::CalibrateArm() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void CalibrateArm::Initialize() {
	SetTimeout(3);
	m_isFinished = false;
	m_switchdelaycount=0;
	if(Intake::GetInstance()->IsClosedLoop())
		Intake::GetInstance()->ConfigureOpenLoop();
}

// Called repeatedly when this Command is scheduled to run
void CalibrateArm::Execute() {
	Intake::GetInstance()->SetArm(-.4);
	if(Intake::GetInstance()->IsIntakeDown()) {
		m_switchdelaycount++;
	}
	if(m_switchdelaycount == m_switchdelay) {
		Intake::GetInstance()->ConfigureClosedLoop();
		m_isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CalibrateArm::IsFinished() {
	return m_isFinished || IsTimedOut();
}

// Called once after isFinished returns true
void CalibrateArm::End() {
	if(!Intake::GetInstance()->IsClosedLoop()) {
		std::cout << "error: could not calibrate arm" << std::endl;
		Intake::GetInstance()->SetArm(0); //Stop Arm
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalibrateArm::Interrupted() {
	End();
}
