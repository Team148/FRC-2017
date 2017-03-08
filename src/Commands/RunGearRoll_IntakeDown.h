#ifndef RunGearRoll_IntakeDown_H
#define RunGearRoll_IntakeDown_H

#include "../CommandBase.h"

class RunGearRoll_IntakeDown : public CommandBase {
public:
	RunGearRoll_IntakeDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_IsFinished = false;

};

#endif  // RunGearRoll_IntakeDown_H
