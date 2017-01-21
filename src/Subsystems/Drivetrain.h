#ifndef Drivetrain_H
#define Drivetrain_H

#include <Commands/Subsystem.h>
#include "CANTalon.h"
#include "RobotMap.h"
#include "WPILib.h"

class Drivetrain : public Subsystem {
private:

	CANTalon* m_leftMotor1;
	CANTalon* m_leftMotor2;
	CANTalon* m_leftMotor3;
	CANTalon* m_rightMotor1;
	CANTalon* m_rightMotor2;
	CANTalon* m_rightMotor3;

	RobotDrive *m_drive;
	Drivetrain();
	static Drivetrain *m_instance;
public:

	static Drivetrain* GetInstance();
	void InitDefaultCommand();
	void Arcade(float ystick, float xstick);
	void SetBrakeMode(bool on);
	void Reenable();
};

#endif  // Drivetrain_H
