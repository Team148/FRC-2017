#include "DriveStraightTMP.h"

DriveStraightTMP::DriveStraightTMP(double distance, double velocity, double endVelocity, double positionTolerance, double timeOut) {
	Requires(Drivetrain::GetInstance());
	m_startPosition = ((double)Drivetrain::GetInstance()->GetLeftDistance() + (double)Drivetrain::GetInstance()->GetRightDistance()) / 2.0;

	m_endPosition = distance + m_startPosition;
	m_startTime = Timer::GetFPGATimestamp();
	m_endVelocity = endVelocity;

	if(velocity > DRIVETRAIN_MAX_VEL)
		velocity = DRIVETRAIN_MAX_VEL;

	if(endVelocity > DRIVETRAIN_MAX_VEL)
		m_endVelocity = DRIVETRAIN_MAX_VEL;

	if(timeOut > 0.0)
		SetTimeout(timeOut);

	m_positionTolerance = positionTolerance;

	m_profile = new TrapezoidalProfile(velocity, (double)DRIVETRAIN_MAX_ACCEL, (double)DRIVETRAIN_MAX_DECEL);
}

// Called just before this Command runs the first time
void DriveStraightTMP::Initialize() {
	m_lastTime = Timer::GetFPGATimestamp();

	//check that the Drivetrain is in closed loop
	if(!Drivetrain::GetInstance()->isClosedLoop())
		Drivetrain::GetInstance()->configClosedLoop();

	Drivetrain::GetInstance()->SetBrakeMode(true);

}

// Called repeatedly when this Command is scheduled to run
void DriveStraightTMP::Execute() {
	double currentTime = Timer::GetFPGATimestamp();
	double currentPosition = ((double)Drivetrain::GetInstance()->GetLeftDistance() + (double)Drivetrain::GetInstance()->GetRightDistance()) / 2.0;
	double currentVelocity = ((Drivetrain::GetInstance()->GetLeftVelocity() + Drivetrain::GetInstance()->GetRightVelocity()) / 2.0);

	double distance = m_endPosition - currentPosition;

	m_profile->Update(distance, currentVelocity, m_endVelocity, currentTime - m_lastTime);

	double curVel = m_profile->GetVelocity();

	double leftVel = curVel;
	double rightVel = curVel;

	Drivetrain::GetInstance()->SetLeft((float)Drivetrain::GetInstance()->IPStoRPM(leftVel));
	Drivetrain::GetInstance()->SetRight((float)Drivetrain::GetInstance()->IPStoRPM(rightVel));

	m_lastTime = currentTime;

	if((abs(curVel - m_endVelocity) < 0.5) && (abs(distance < m_positionTolerance)))
		m_isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightTMP::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveStraightTMP::End() {
	Drivetrain::GetInstance()->SetLeft(0);
	Drivetrain::GetInstance()->SetRight(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightTMP::Interrupted() {
	End();

}
