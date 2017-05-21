#ifndef SetTurretAngle_H
#define SetTurretAngle_H

#include "../CommandBase.h"

class SetTurretAngle : public CommandBase {
public:
	SetTurretAngle(double angle, bool delay = true);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = false;
	bool m_delay;
	double m_init_angle = 0;
	double m_input_angle = 0;
	double m_angle_error;
	int tolerance_delay=0;

};

#endif  // SetTurretAngle_H
