#ifndef SetAgitator_H
#define SetAgitator_H

#include "../../CommandBase.h"

class SetAgitator : public CommandBase {
public:
	SetAgitator(bool on, double timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_on = false;
	double m_timeout = 0.0;
	bool m_IsFinished = false;
};

#endif  // SetAgitator_H
