#ifndef ClosedShooterSpeed_H
#define ClosedShooterSpeed_H

#include "../CommandBase.h"

class ClosedShooterSpeed : public CommandBase {
public:
	ClosedShooterSpeed();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ClosedShooterSpeed_H
