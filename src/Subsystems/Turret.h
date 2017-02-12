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
	//2-4 limit switches  2 for max/min, 1-2 for "home" positions.  The Max/Min Switches could be softwareLimits

	DigitalInput* m_HomeSwitch;

	static Turret* m_instance;
	Turret();
	bool m_IsClosedLoop;

public:
	static Turret* GetInstance();
	void InitDefaultCommand();
	void ConfigOpenLoop();
	void ConfigClosedLoop();
	bool IsClosedLoop();

	void SetActualPosition(double position = 0);
	void SetOpen();
	void SetAngle(float angle);
	void Reset(float actual);
	bool IsHomed();

};

#endif  // Turret_H
