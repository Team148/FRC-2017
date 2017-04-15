#ifndef TargetBoiler_H
#define TargetBoiler_H

#include "../../CommandBase.h"

class TargetBoiler : public CommandBase {
public:
	TargetBoiler(bool enable);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool m_enable;
};

#endif  // TargetBoiler_H
