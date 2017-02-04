#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "CANTalon.h"

class Shooter : public Subsystem {
private:
	CANTalon* m_Motor1;
	CANTalon* m_Motor2;

	Shooter();
	static Shooter* m_instance;
	int m_rpm=0;

public:

	static Shooter* GetInstance();
	void InitDefaultCommand();
	void ConfigureOpenLoop();
	void SetOpenLoop(float value);
	void SetClosedLoop(int rpm);
};

#endif  // Shooter_H
