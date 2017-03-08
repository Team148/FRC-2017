#include "CalibrateArm.h"

CalibrateArm::CalibrateArm() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void CalibrateArm::Initialize() {
	SetTimeout(2.5);
	m_isFinished = false;
	m_switchdelaycount = 0;
	if(Intake::GetInstance()->IsClosedLoop())
		Intake::GetInstance()->ConfigureOpenLoop();
	Intake::GetInstance()->SetCalibrating(1);
}

// Called repeatedly when this Command is scheduled to run
void CalibrateArm::Execute() {
	Intake::GetInstance()->SetArm(-0.70);
	if(Intake::GetInstance()->IsIntakeDown())
	{
		m_switchdelaycount++;
		Intake::GetInstance()->SetArm(-0.35);
		if(m_switchdelaycount >= m_switchdelay)
		{
			Intake::GetInstance()->ConfigureClosedLoop();
			Intake::GetInstance()->SetArm(0.0);
			m_isFinished = true;
		}
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
	else
		Intake::GetInstance()->SetArmAngle(INTAKE_ARM_POSITION_UP);
	Intake::GetInstance()->SetCalibrating(false);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalibrateArm::Interrupted() {

}
