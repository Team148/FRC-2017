#ifndef SetIntake_H
#define SetIntake_H

#include "Commands/InstantCommand.h"

class SetIntake : public InstantCommand {
public:
	SetIntake(float angle);
	void Initialize();
private:
	float m_angle;
};

#endif  // SetIntake_H
