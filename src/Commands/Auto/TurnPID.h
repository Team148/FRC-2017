#ifndef TurnPID_H
#define TurnPID_H

#include "../../CommandBase.h"
#include "WPIlib.h"
#include "constants.h"

class TurnPID : public CommandBase {
public:
	TurnPID(float degrees);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float m_setpoint;
	bool m_isFinished = 0;
	//PIDController* m_controller;
	float m_Kp = DRIVETRAIN_TURN_P;
	float m_Ki = DRIVETRAIN_TURN_I;
	float m_initalAngle = 0;
};

#endif  // TurnPID_H
