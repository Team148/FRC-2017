#ifndef SetTurretAngle_H
#define SetTurretAngle_H

#include "../CommandBase.h"

class SetTurretAngle : public CommandBase {
public:
	SetTurretAngle(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = false;
	double m_init_angle = 0;
	double m_input_angle;
	double m_final_angle;
	int tolerance_delay=0;

};

#endif  // SetTurretAngle_H
