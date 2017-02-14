#ifndef SetIntakeArm_H
#define SetIntakeArm_H

#include "../CommandBase.h"
#include "Subsystems/Intake.h"

class SetIntakeArm : public CommandBase {
public:
	SetIntakeArm(float angle, float time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float m_angle = 0.0;
	float m_time = 0.0;
	float m_startTime = 0.0;
	float m_currentTime = 0.0;
	bool m_IsFinished = false;
};

#endif  // SetIntakeArm_H
