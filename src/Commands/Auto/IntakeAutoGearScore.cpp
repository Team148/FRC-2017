#include <Commands/Auto/IntakeAutoGearScore.h>
#include <Commands/AutoGearScoreSub.h>

#include "Subsystems/Intake.h"

IntakeAutoGearScore::IntakeAutoGearScore() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Intake::GetInstance());
}

// Called just before this Command runs the first time
void IntakeAutoGearScore::Initialize()
{
	m_IsFinished = false;
	m_startTime = Timer::GetFPGATimestamp();
	//Intake::GetInstance()->SetGear(.05);
	Intake::GetInstance()->SetArm(INTAKE_ARM_GEAR_POSITION);
	//Scheduler::GetInstance()->AddCommand(new AutoGearScoreSub());
}

// Called repeatedly when this Command is scheduled to run
void IntakeAutoGearScore::Execute()
{
	Intake::GetInstance()->SetGear(.05);
	//Intake::GetInstance()->SetArm(INTAKE_ARM_GEAR_POSITION);

	if(Timer::GetFPGATimestamp() - m_startTime >= m_delay)
	{
		Intake::GetInstance()->SetGear(0.0);
		m_IsFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeAutoGearScore::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void IntakeAutoGearScore::End() {
	Intake::GetInstance()->SetGear(0.0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeAutoGearScore::Interrupted() {
	End();
}
