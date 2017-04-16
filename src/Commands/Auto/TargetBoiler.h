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
	int m_expiration = 0;
};

#endif  // TargetBoiler_H
