#ifndef Turret_H
#define Turret_H

#include <iostream>
#include <Commands/Subsystem.h>
#include "../RobotMap.h"
#include "CanTalon.h"
#include "Constants.h"
#include "WPIlib.h"

class Turret : public Subsystem {
private:
	//1 CanTalon with integrated encoder feedback
	CANTalon* m_Motor;
	//2-4 limit switches  2 for max/min, 1-2 for "home" positions.
	DigitalInput* m_MaxSwitch;
	DigitalInput* m_MinSwitch;
	DigitalInput* m_HomeSwitch;

	static Turret* m_instance;
	Turret();

public:
	static Turret* GetInstance();
	void InitDefaultCommand();
	void ConfigOpenLoop();
	void ConfigClosedLoop();

	void SetOpen();
	void SetAngle();
};

#endif  // Turret_H
