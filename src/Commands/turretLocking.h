#ifndef turretLocking_H
#define turretLocking_H

#include "Commands/InstantCommand.h"

class turretLocking : public InstantCommand {
public:
	turretLocking(bool lock);
	void Initialize();
private:
	bool m_lock = false;
};

#endif  // turretLocking_H
