#ifndef TankDriveJoystick_H
#define TankDriveJoystick_H

#include "../CommandBase.h"

class TankDriveJoystick : public CommandBase {
public:
	TankDriveJoystick();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TankDriveJoystick_H
