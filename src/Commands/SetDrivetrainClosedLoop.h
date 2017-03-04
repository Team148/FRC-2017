#ifndef SetDrivetrainClosedLoop_H
#define SetDrivetrainClosedLoop_H

#include "Commands/InstantCommand.h"

class SetDrivetrainClosedLoop : public InstantCommand {
public:
	SetDrivetrainClosedLoop(bool closedLoop);
	void Initialize();
private:
	bool m_closedLoop = false;
};

#endif  // SetDrivetrainClosedLoop_H
