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
	void Tank(float leftstick, float rightstick);
	void SetBrakeMode(bool on);
	void SetLeft(float val);
	void SetRight(float val);

	void Reenable();
	double GetAngle();
	int GetEncoderVelocity();
	int GetLeftVelocity();
	int GetRightVelocity();
	int GetLeftDistance();
	int GetRightDistance();

	void configClosedLoop();
	bool isClosedLoop();
	void configOpenLoop();
	float IPStoRPM(float val);
	float RPMtoIPS(float val);
	float RotationtoInch(float val);
	float InchtoRotation(float val);
	void ZeroSensors();
};

#endif  // Drivetrain_H
