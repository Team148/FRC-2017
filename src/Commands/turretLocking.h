#ifndef turretLocking_H
#define turretLocking_H

#include "../CommandBase.h"


class turretLocking : public Command {
public:
	turretLocking(bool lock);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_lock = false;
	bool m_IsFinished = false;
};

#endif  // turretLocking_H
