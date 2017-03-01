#include "SetBallGearUntilBeam.h"
#include "Subsystems/Intake.h"


SetBallGearUntilBeam::SetBallGearUntilBeam() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void SetBallGearUntilBeam::Initialize() {

	SetTimeout(3.0);
	m_isFinished = false;


}

// Called repeatedly when this Command is scheduled to run
void SetBallGearUntilBeam::Execute() {

	Intake::GetInstance()->SetBall(1.0);
	Intake::GetInstance()->SetGear(1.0);
//	if(Intake::GetInstance()->IsBeamBroke())
//	{
//		m_isFinished = true;
//	}
}

// Make this return true when this Command no longer needs to run execute()
bool SetBallGearUntilBeam::IsFinished() {
	return m_isFinished || IsTimedOut();
}

// Called once after isFinished returns true
void SetBallGearUntilBeam::End() {
	Intake::GetInstance()->SetBall(0.0);
	Intake::GetInstance()->SetGear(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetBallGearUntilBeam::Interrupted() {

}
