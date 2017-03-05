#include "SetDrivetrainClosedLoop.h"
#include "Subsystems/Drivetrain.h"

SetDrivetrainClosedLoop::SetDrivetrainClosedLoop(bool closedLoop) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Drivetrain::GetInstance());
	m_closedLoop = closedLoop;
}

// Called once when the command executes
void SetDrivetrainClosedLoop::Initialize() {
	if(m_closedLoop)
	{
		Drivetrain::GetInstance()->configClosedLoop();
	}
	else
	{
		Drivetrain::GetInstance()->configOpenLoop();
	}
}
