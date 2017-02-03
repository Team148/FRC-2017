#ifndef Turret_H
#define Turret_H

#include <iostream>
#include <Commands/Subsystem.h>
#include "../RobotMap.h"
#include "CanTalon.h"

class Turret : public Subsystem {
private:
	//1 CanTalon with integrated encoder feedback
	//2-4 limit switches  2 for max/min, 1-2 for "home" positions.
	static Turret* m_instance;
	Turret();
public:
	static Turret* GetInstance();
	void InitDefaultCommand();
	void ConfigOpenLoop();
	void ConfigClosedLoop();

	void SetOpen();
};

#endif  // Turret_H
