#ifndef SetBallGearUntilBeam_H
#define SetBallGearUntilBeam_H

#include "CommandBase.h"

class SetBallGearUntilBeam : public CommandBase {
public:
	SetBallGearUntilBeam();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = false;
};

#endif  // SetBallGearUntilBeam_H
