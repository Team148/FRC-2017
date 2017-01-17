#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include "CANTalon.h"
#include "CanTalonSRX.h"

class Shooter : public Subsystem {
private:
	CANTalon* m_Motor1;
	CANTalon* m_Motor2;
public:
	Shooter();
	void InitDefaultCommand();
};

#endif  // Shooter_H
