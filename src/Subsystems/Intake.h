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
	CANTalon* m_BallMotor;

	Intake();
	static Intake *m_instance;
public:

	static Intake* GetInstance();
	void InitDefaultCommand();
};

#endif  // Intake_H
