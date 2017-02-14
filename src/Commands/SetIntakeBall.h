#ifndef SetIntakeBall_H
#define SetIntakeBall_H

#include "Commands/InstantCommand.h"
#include "Subsystems/Intake.h"

class SetIntakeBall : public InstantCommand {
public:
	SetIntakeBall(float speed);
	void Initialize();

private:
	float m_speed = 0.0;
};

#endif  // SetIntakeBall_H
