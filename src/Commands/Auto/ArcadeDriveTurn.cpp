#include "ArcadeDriveTurn.h"

ArcadeDriveTurn::ArcadeDriveTurn(float angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Drivetrain::GetInstance());
	m_input_angle = angle;
	m_final_angle = m_init_angle + m_input_angle;
	if(m_input_angle < 0)
		m_left_turn = 1;
}

// Called just before this Command runs the first time
void ArcadeDriveTurn::Initialize() {
	m_isFinished=0;
	m_init_angle = Drivetrain::GetInstance()->GetAngle();
	Drivetrain::GetInstance()->configOpenLoop();
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDriveTurn::Execute() {
	float cur_angle = Drivetrain::GetInstance()->GetAngle();

	float cur_err = m_final_angle - cur_angle;

	float stick_input = cur_err*ARCADE_TURN_P;

	//bound input
	if(stick_input > .5)
		stick_input = .5;
	if(stick_input < -.5)
		stick_input = -.5;


	Drivetrain::GetInstance()->Arcade(0,stick_input);

	if(cur_err <.2)
		m_isFinished=1;
}

// Make this return true when this Command no longer needs to run execute()
bool ArcadeDriveTurn::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void ArcadeDriveTurn::End() {
	Drivetrain::GetInstance()->Arcade(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcadeDriveTurn::Interrupted() {
	End();
}
