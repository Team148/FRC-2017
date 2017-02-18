#ifndef Conveyor_H
#define Conveyor_H

#include <Commands/Subsystem.h>
#include <iostream>
#include "CANTalon.h"
#include "CanTalonSRX.h"

class Conveyor : public Subsystem {
private:
	CANTalon* m_lowerMotor;
	CANTalon* m_upperMotor;
	CANTalon* m_climberMotor;

	Conveyor();
	static Conveyor *m_instance;

public:
	static Conveyor* GetInstance();
	void InitDefaultCommand();
	void SetAgitator(float voltage);
	void SetKicker(float voltage);
	void SetClimber(float voltage);
};

#endif  // Conveyor_H
