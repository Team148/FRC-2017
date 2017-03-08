#ifndef StopGearRoll_IntakeUp_H
#define StopGearRoll_IntakeUp_H

#include "../CommandBase.h"

class StopGearRoll_IntakeUp : public CommandBase {
public:
	StopGearRoll_IntakeUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_IsFinished = false;
	float m_startTime = 0.0;
	float m_currentTime = 0.0;

};

#endif  // StopGearRoll_IntakeUp_H
