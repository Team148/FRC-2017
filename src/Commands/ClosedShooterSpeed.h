#ifndef ClosedShooterSpeed_H
#define ClosedShooterSpeed_H

<<<<<<< HEAD
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
=======
#include "../CommandBase.h"

class ClosedShooterSpeed : public CommandBase {
public:
	ClosedShooterSpeed();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
>>>>>>> branch 'ShooterPrototype' of https://github.com/Team148/FRC-2017.git
};

#endif  // ClosedShooterSpeed_H
