#ifndef SetAgitator_H
#define SetAgitator_H

#include "../../CommandBase.h"

class SetAgitator : public CommandBase {
public:
	SetAgitator(bool on);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_on = false;
	bool m_IsFinished = false;
};

#endif  // SetAgitator_H
