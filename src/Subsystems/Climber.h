#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include "CanTalon.h"

class Climber : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon* m_climberMotor;
	CANTalon* m_climberMotor2;

	static Climber *m_instance;
	Climber();

public:
	static Climber* GetInstance();
	void InitDefaultCommand();
	void Set(float voltage);
};

#endif  // Climber_H
