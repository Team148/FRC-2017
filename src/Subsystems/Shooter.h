#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "CANTalon.h"
#include "CanTalonSRX.h"

class Shooter : public Subsystem {
private:
	CANTalon* m_Motor1;
	CANTalon* m_Motor2;

	Shooter();
	static Shooter* m_instance;

public:

	static Shooter* GetInstance();
	void InitDefaultCommand();
	void ConfigureOpenLoop();
	void SetOpenLoop(float value);
	void ConfigureClosedLoop();
	void SetClosedLoop(float speed);
};

#endif  // Shooter_H
