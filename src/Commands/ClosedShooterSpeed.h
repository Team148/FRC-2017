#ifndef ClosedShooterSpeed_H
#define ClosedShooterSpeed_H

#include "Subsystems/Shooter.h"
#include "../CommandBase.h"
#include "OI.h"

class ClosedShooterSpeed : public Command {
public:
	ClosedShooterSpeed(int adj_speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	int m_speed;
};

#endif  // ClosedShooterSpeed_H
