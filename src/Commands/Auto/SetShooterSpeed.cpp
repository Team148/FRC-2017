#include "SetShooterSpeed.h"
#include "Subsystems/Shooter.h"

SetShooterSpeed::SetShooterSpeed(int rpm, bool useRamp) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Shooter::GetInstance());
	m_rpm = rpm;
	m_useRamp = useRamp;
}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize() {
	if(m_useRamp)
	{
		Shooter::GetInstance()->SetVoltageRamp(10.0);
	}
	Shooter::GetInstance()->SetRPM(m_rpm);
	m_startTime = Timer::GetFPGATimestamp();

}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute()
{
	if(m_useRamp)
	{
		if(Timer::GetFPGATimestamp() - m_startTime >= 1.5)
		{
			m_IsFinished = true;
		}
	}
	else
	{
		m_IsFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished() {
	return m_IsFinished;
}

// Called once after isFinished returns true
void SetShooterSpeed::End()
{
	Shooter::GetInstance()->SetVoltageRamp(0.0);
	Shooter::GetInstance()->SetRPM(m_rpm);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterSpeed::Interrupted() {

}
