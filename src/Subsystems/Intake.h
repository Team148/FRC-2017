#ifndef Intake_H
#define Intake_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "CANTalon.h"
#include "CanTalonSRX.h"

class Intake : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon* m_ArmMotor;
	CANTalon* m_GearMotor;
	CANTalon* m_BallMotor_1;
	CANTalon* m_BallMotor_2;

	Intake();
	static Intake *m_instance;
public:

	static Intake* GetInstance();
	void InitDefaultCommand();

	void SetArm(float val);
	void SetGear(float val);
	void SetBall(float val);

	void SetBrakeMode(bool on);
	void ConfigureOpenLoop();
	void ConfigureClosedLoop();
};

#endif  // Intake_H
