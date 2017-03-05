#ifndef SetShooterSpeed_H
#define SetShooterSpeed_H

#include "../../CommandBase.h"

class SetShooterSpeed : public CommandBase {
public:
	SetShooterSpeed(int rpm);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int m_rpm = 0;
	bool m_IsFinished = false;
};

#endif  // SetShooterSpeed_H
