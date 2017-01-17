#ifndef Conveyor_H
#define Conveyor_H

#include <Commands/Subsystem.h>
#include "CANTalon.h"
#include "CanTalonSRX.h"

class Conveyor : public Subsystem {
private:
	CANTalon* m_lowerMotor;
	CANTalon* m_upperMotor;

public:
	Conveyor();
	void InitDefaultCommand();
};

#endif  // Conveyor_H
