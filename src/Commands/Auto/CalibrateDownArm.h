#ifndef CalibrateDownArm_H
#define CalibrateDownArm_H

#include "../../CommandBase.h"
#include "Subsystems/Intake.h"

class CalibrateDownArm : public CommandBase {
public:
	CalibrateDownArm(bool leaveArmDown);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = false;
	int m_switchdelay = 5;
	int m_switchdelaycount = 0;
	bool m_armDown = false;
};

#endif  // CalibrateDownArm_H
