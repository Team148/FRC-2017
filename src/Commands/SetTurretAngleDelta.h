#ifndef SetTurretAngleDelta_H
#define SetTurretAngleDelta_H

#include "../CommandBase.h"

class SetTurretAngleDelta : public CommandBase {
public:
	SetTurretAngleDelta(double angle_delta, bool delay = true);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = false;
	bool m_delay;
	double m_init_angle = 0;
	double m_target_angle;
	double m_angle_error;
	int tolerance_delay=0;

};

#endif  // SetTurretAngleDelta_H
