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
};

#endif  // CalibrateArm_H
