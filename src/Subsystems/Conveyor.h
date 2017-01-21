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

	Conveyor();
	static Conveyor *m_instance;

public:
	static Conveyor* GetInstance();
	void InitDefaultCommand();
	void SetLower(float voltage);
	void SetUpper(float voltage);
};

#endif  // Conveyor_H
