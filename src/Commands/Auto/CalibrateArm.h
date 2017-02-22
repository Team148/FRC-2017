#ifndef CalibrateArm_H
#define CalibrateArm_H

#include "../../CommandBase.h"
#include "Subsystems/Intake.h"

class CalibrateArm : public CommandBase {
public:
	CalibrateArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = false;
	int m_switchdelay = 3;
	int m_switchdelaycount = 0;
};

#endif  // CalibrateArm_H
