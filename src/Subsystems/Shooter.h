#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "Constants.h"
#include "CANTalon.h"
#include "ctre/PCM.h"
#include "WPILib.h"

class Shooter : public Subsystem {
private:
	CANTalon* m_Motor1;
	CANTalon* m_Motor2;

	PCM* m_pcm;
	Compressor *m_c;
	Shooter();
	static Shooter* m_instance;
	int m_rpm = 0;
	bool m_isClosedLoop=false;
public:

	static Shooter* GetInstance();
	void InitDefaultCommand();
	void ConfigureClosedLoop();
	void ConfigureOpenLoop();
	void SetOpenLoop(float value);
	void SetRPM(int rpm);
	int GetRPM();

	void SetFlashlightOn(bool mode);

};

#endif  // Shooter_H
