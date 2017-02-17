#ifndef Wait_H
#define Wait_H

#include "../../CommandBase.h"

class Wait : public CommandBase {
public:
	Wait(double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_waittime;
	bool m_isFinished = false;
	double m_starttime=0;
};

#endif  // Wait_H
