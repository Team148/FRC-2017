#ifndef SetIntakeGear_H
#define SetIntakeGear_H

#include "Commands/InstantCommand.h"
#include "Subsystems/Intake.h"

class SetIntakeGear : public InstantCommand {
public:
	SetIntakeGear(float speed);
	void Initialize();
private:
	float m_speed = 0.0;
};

#endif  // SetIntakeGear_H
