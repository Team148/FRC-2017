#ifndef SetKicker_H
#define SetKicker_H

#include "../../CommandBase.h"

class SetKicker : public CommandBase {
public:
	SetKicker(bool on, double timeout);
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

#endif  // SetKicker_H
