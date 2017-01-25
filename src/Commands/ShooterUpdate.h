#ifndef ShooterUpdate_H
#define ShooterUpdate_H

#include "../CommandBase.h"

class ShooterUpdate : public Command {
public:
	float m_speed;

	ShooterUpdate();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();



};

#endif  // ShooterUpdate_H
