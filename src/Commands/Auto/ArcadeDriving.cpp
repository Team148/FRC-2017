#include "ArcadeDriving.h"

ArcadeDriving::ArcadeDriving(float dist) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Drivetrain::GetInstance());
	m_travel_distance = dist;
}

// Called just before this Command runs the first time
void ArcadeDriving::Initialize() {
	m_isFinished=0;
	//reset sensors
	Drivetrain::GetInstance()->ZeroSensors();
	//check gyro angle
	m_init_angle = Drivetrain::GetInstance()->GetAngle();
	m_integral_err=0;
	//convert inches to rotations, to ticks
	m_travel_distance = Drivetrain::GetInstance()->InchtoRotation(m_travel_distance)*4*256;
	Drivetrain::GetInstance()->configOpenLoop();
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDriving::Execute() {
	float cur_lpos = Drivetrain::GetInstance()->GetLeftDistance();
	float cur_rpos = Drivetrain::GetInstance()->GetRightDistance();
	float cur_angle = Drivetrain::GetInstance()->GetAngle();

	float dist_error = m_travel_distance - cur_lpos;  //remaining error
	m_integral_err += dist_error*.02;
	float stick_input = dist_error* ARCADE_DRIVE_P + m_integral_err*ARCADE_DRIVE_I;
	//bound input
	if(stick_input > .5)
		stick_input = .5;
	if(stick_input < -.5)
		stick_input = -.5;

	float cur_err = m_init_angle - cur_angle;
	float gyro_comp = ARCADE_DRIVE_GYRO_P*cur_err;

	Drivetrain::GetInstance()->Arcade(stick_input,gyro_comp);

	if(abs(cur_err)<=ARCADE_TURN_TOLERANCE) {
		tolerance_delay++;
		if(tolerance_delay > 5)
			m_isFinished=1;
	}
	else
		tolerance_delay=0;
}

// Make this return true when this Command no longer needs to run execute()
bool ArcadeDriving::IsFinished() {
	return m_isFinished;
}

// Called once after isFinished returns true
void ArcadeDriving::End() {
	Drivetrain::GetInstance()->Arcade(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcadeDriving::Interrupted() {
	End();
}
