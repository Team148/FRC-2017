#ifndef Intake_H
#define Intake_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "CANTalon.h"
#include "CanTalonSRX.h"
#include "Constants.h"
#include "WPIlib.h"


class Intake : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon* m_ArmMotor;
	CANTalon* m_GearMotor;
	CANTalon* m_BallMotor_1;

	//2 limit switches 	1 for down 	1 for up
	DigitalInput* m_DownLimit;
	DigitalInput* m_UpLimit;

	//BeamBreak
	AnalogInput* m_beam;

	Intake();
	static Intake *m_instance;
	bool m_isHomed = 0;
	bool m_isClosedLoop = 0;
	bool m_calibrating = 0;
public:
	static Intake* GetInstance();
	void InitDefaultCommand();

	void SetArm(float val);
	void SetGear(float val);
	void SetBall(float val);

	void SetBrakeMode(bool on);
	void ConfigureOpenLoop();
	void ConfigureClosedLoop();
	bool IsClosedLoop();
	void SetCalibrating(bool calibrate);
	bool IsCalibrating();
	void ResetArm(float actual_pos);

	bool IsIntakeDown();
	bool IsIntakeUp();
	void SetArmAngle(float angle);
	float GetArmAngle();
	bool IsBeamBroke();
	void setPID(double P, double I, double D);
	int isSensorPluggedIn();


};

#endif  // Intake_H
