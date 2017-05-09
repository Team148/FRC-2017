#include "DriveStraightTMP.h"

DriveStraightTMP::DriveStraightTMP(double distance, double velocity, double endVelocity, double positionTolerance, double timeOut) {
	Requires(Drivetrain::GetInstance());
	//m_startPosition = ((double)Drivetrain::GetInstance()->GetLeftDistance() + (double)Drivetrain::GetInstance()->GetRightDistance()) / 2.0;
	m_startPosition = Drivetrain::GetInstance()->GetPositionInch();

	std::cout << "Start Position: " << m_startPosition << std::endl;

	m_endPosition = distance + m_startPosition;


	m_startTime = Timer::GetFPGATimestamp();
	m_endVelocity = endVelocity;
	m_initAngle = Drivetrain::GetInstance()->GetAngle();

	std::cout << "End Position: " << m_endPosition << std::endl;

	if(velocity > DRIVETRAIN_MAX_VEL)
		velocity = DRIVETRAIN_MAX_VEL;

	if(endVelocity > DRIVETRAIN_MAX_VEL)
		m_endVelocity = DRIVETRAIN_MAX_VEL;

	if(timeOut > 0.0)
		SetTimeout(timeOut);

	m_positionTolerance = positionTolerance;

	m_profile = new TrapezoidalProfile(velocity, (double)DRIVETRAIN_MAX_ACCEL, (double)DRIVETRAIN_MAX_DECEL);
	m_PID = new SynchronousPID(kDriveHeadingVelocityKp,kDriveHeadingVelocityKi,kDriveHeadingVelocityKd);
	m_PID->SetSetPoint(m_initAngle);
//	std::cout << "DriveTMP Constructed" << std::endl;
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
	//double currentPosition = ((double)Drivetrain::GetInstance()->GetLeftDistance() + (double)Drivetrain::GetInstance()->GetRightDistance()) / 2.0;
	double currentPosition = Drivetrain::GetInstance()->GetPositionInch();
	//double currentVelocity = ((Drivetrain::GetInstance()->GetLeftVelocity() + Drivetrain::GetInstance()->GetRightVelocity()) / 2.0);
	double currentVelocity = Drivetrain::GetInstance()->GetVelocityIPS();

	double distance = m_endPosition - currentPosition;

	m_profile->Update(distance, currentVelocity, m_endVelocity, currentTime - m_lastTime);

	double curVel = m_profile->GetVelocity();
	double turnSpeed = m_PID->calculate(Drivetrain::GetInstance()->GetAngle());

	double leftVel = curVel + turnSpeed;
	double rightVel = curVel - turnSpeed;


	Drivetrain::GetInstance()->SetLeft((float)Drivetrain::GetInstance()->IPStoRPM(leftVel));
	Drivetrain::GetInstance()->SetRight((float)Drivetrain::GetInstance()->IPStoRPM(rightVel));

	std::cout << "Drive Velocity: " << curVel << std::endl;
	std::cout << "Distance: " << distance << std::endl;
	frc::SmartDashboard::PutNumber("ProfileVelError", curVel-Drivetrain::GetInstance()->GetVelocityIPS());
	m_lastTime = currentTime;

	if((abs(curVel - m_endVelocity) < 0.5) && (abs(distance) < m_positionTolerance))
		m_isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightTMP::IsFinished() {
	return m_isFinished || IsTimedOut();
}

// Called once after isFinished returns true
void DriveStraightTMP::End() {
	Drivetrain::GetInstance()->SetLeft(0);
	Drivetrain::GetInstance()->SetRight(0);
	std::cout << "Ended";
	CurrentState();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightTMP::Interrupted() {
	End();

}

void DriveStraightTMP::CurrentState(){
	std::cout 	<< "D:" << m_endPosition - ((double)Drivetrain::GetInstance()->GetLeftDistance() + (double)Drivetrain::GetInstance()->GetRightDistance()) / 2.0
				<< "V:" << ((Drivetrain::GetInstance()->GetLeftVelocity() + Drivetrain::GetInstance()->GetRightVelocity()) / 2.0) << std::endl;
}
