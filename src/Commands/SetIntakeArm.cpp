#include "SetIntakeArm.h"

SetIntakeArm::SetIntakeArm(float angle, float time) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
	m_angle = angle;
	m_time = time;
	if(m_time <= 0.0) m_time = .01;

}

// Called just before this Command runs the first time
void SetIntakeArm::Initialize() {

	m_IsFinished = false;
	m_startTime = Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void SetIntakeArm::Execute() {

	m_currentTime = Timer::GetFPGATimestamp() - m_startTime;
	Intake::GetInstance()->SetArmAngle((m_angle/m_time)*m_currentTime);
	if(m_currentTime >= m_time)
		{
			m_IsFinished = true;
			Intake::GetInstance()->SetArmAngle(m_angle);
		}
}

// Make this return true when this Command no longer needs to run execute()
bool SetIntakeArm::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void SetIntakeArm::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetIntakeArm::Interrupted() {

}
