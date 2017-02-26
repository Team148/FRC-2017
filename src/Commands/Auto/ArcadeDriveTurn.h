#ifndef ArcadeDriveTurn_H
#define ArcadeDriveTurn_H

#include "../../CommandBase.h"

class ArcadeDriveTurn : public CommandBase {
public:
	ArcadeDriveTurn(float angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished = 0;
	float m_init_angle=0;
	float m_input_angle;
	float m_final_angle;
	bool m_left_turn = 0;
};

#endif  // ArcadeDriveTurn_H
