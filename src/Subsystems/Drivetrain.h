#ifndef Drivetrain_H
#define Drivetrain_H

#include <Commands/Subsystem.h>
#include "CANTalon.h"
#include "RobotMap.h"
#include "WPILib.h"
#include "Constants.h"

class Drivetrain : public Subsystem {
private:

	CANTalon* m_leftMotor1;
	CANTalon* m_leftMotor2;
	CANTalon* m_leftMotor3;
	CANTalon* m_rightMotor1;
	CANTalon* m_rightMotor2;
	CANTalon* m_rightMotor3;

	RobotDrive *m_drive;
	PowerDistributionPanel* m_pdp;
	ADXRS450_Gyro *m_gyro;

	Drivetrain();
	static Drivetrain *m_instance;

	bool m_closedLoop = 0;
public:

	static Drivetrain* GetInstance();
	void InitDefaultCommand();
	void Arcade(float ystick, float xstick);
	void SetBrakeMode(bool on);
	void SetLeft(float val);
	void SetRight(float val);
	void Reenable();
	double GetAngle();
	int GetEncoderVelocity();

	void configClosedLoop();
	bool isClosedLoop();
	void configOpenLoop();
	float IPStoRPM(float val);
};

#endif  // Drivetrain_H
