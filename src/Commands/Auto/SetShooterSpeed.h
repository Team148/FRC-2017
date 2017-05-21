#ifndef SetShooterSpeed_H
#define SetShooterSpeed_H

#include "../../CommandBase.h"

class SetShooterSpeed : public CommandBase {
public:
	SetShooterSpeed(int rpm, bool useRamp = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int m_rpm = 0;
	float m_startTime = 0.0;
	bool m_IsFinished = false;
	bool m_useRamp = false;
};

#endif  // SetShooterSpeed_H
