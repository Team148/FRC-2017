#include "ArcadeDriveTurn.h"

ArcadeDriveTurn::ArcadeDriveTurn(float angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Drivetrain::GetInstance());
	m_input_angle = angle;
	m_init_angle = Drivetrain::GetInstance()->GetAngle();
	m_final_angle = m_init_angle + m_input_angle;
	if(m_input_angle < 0)
		m_left_turn = 1;
}

// Called just before this Command runs the first time
void ArcadeDriveTurn::Initialize() {
	m_isFinished=0;
	tolerance_delay=0;
	SetTimeout(5.0);
	//Drivetrain::GetInstance()->ResetGyro();
	m_integral_err=0;
	m_init_angle = Drivetrain::GetInstance()->GetAngle();
	m_final_angle = m_init_angle + m_input_angle;
	std::cout <<"info: final_angle " << m_final_angle << std::endl;
	Drivetrain::GetInstance()->configOpenLoop();
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDriveTurn::Execute() {
	float cur_angle = Drivetrain::GetInstance()->GetAngle();

	float cur_err = m_final_angle - cur_angle;
	m_integral_err += cur_err*.02;

	float stick_input = cur_err*ARCADE_TURN_P + ARCADE_TURN_I*m_integral_err;

	//bound input
	if(stick_input > .57)
		stick_input = .57;
	if(stick_input < -.57)
		stick_input = -.57;


	Drivetrain::GetInstance()->Arcade(0,stick_input);
	//std::cout <<"info: cur_err " << cur_err << std::endl;

	if(abs(cur_err)<=ARCADE_TURN_TOLERANCE) {
		tolerance_delay++;
		if(tolerance_delay > 5)
			m_isFinished=1;
	}
	else
		tolerance_delay=0;
}

// Make this return true when this Command no longer needs to run execute()
bool ArcadeDriveTurn::IsFinished() {
	return m_isFinished || 	IsTimedOut();
;
}

// Called once after isFinished returns true
void ArcadeDriveTurn::End() {
	Drivetrain::GetInstance()->Arcade(0,0);
	std::cout <<"info: final_angle" << Drivetrain::GetInstance()->GetAngle() << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcadeDriveTurn::Interrupted() {
	End();
}
