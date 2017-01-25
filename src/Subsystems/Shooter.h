#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "CANTalon.h"
#include "CanTalonSRX.h"


class Shooter : public Subsystem {
private:


	Shooter();
	static Shooter* m_instance;

public:
	CANTalon* m_Motor1;
	CANTalon* m_Motor2;
	static Shooter* GetInstance();
	void InitDefaultCommand();
	void ConfigureOpenLoop();
	void SetOpenLoop(float value);
	void ConfigureClosedLoop();
	void SetClosedLoop(float speed);

	float cur_speed =0;
};

#endif  // Shooter_H
