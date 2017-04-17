#ifndef AutoAim_H
#define AutoAim_H

#include "../CommandBase.h"
#include "Subsystems/Turret.h"
#include "Subsystems/Shooter.h"

class AutoAim : public CommandBase {
public:
	AutoAim();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float m_yaw_offset;
	float m_yaw_final;

	bool m_isFinished = false;

};

#endif  // AutoAim_H
