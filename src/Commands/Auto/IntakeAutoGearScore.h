#ifndef IntakeAutoGearScore_H
#define IntakeAutoGearScore_H

#include "CommandBase.h"

class IntakeAutoGearScore : public CommandBase {
public:
	IntakeAutoGearScore();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_IsFinished = false;
	int m_startTime = 0.0;
	int m_delay = 0.5;
};

#endif  // IntakeAutoGearScore_H
