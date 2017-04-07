#ifndef SetFlashlight_H
#define SetFlashlight_H

#include "Commands/InstantCommand.h"

class SetFlashlight : public InstantCommand {
public:
	SetFlashlight(bool set);
	void Initialize();
private:
	bool m_set = false;
};

#endif  // SetFlashlight_H
