#ifndef SetKicker_H
#define SetKicker_H

#include "../../CommandBase.h"

class SetKicker : public CommandBase {
public:
	SetKicker(bool on);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_on = false;
	bool m_IsFinished = false;
};

#endif  // SetKicker_H
