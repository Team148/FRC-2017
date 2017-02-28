#ifndef ArcadeDriving_H
#define ArcadeDriving_H

#include "../../CommandBase.h"
#include "math.h"

class ArcadeDriving : public CommandBase {
public:
	ArcadeDriving(float dist);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float m_travel_distance;
	int tolerance_delay;
	bool m_isFinished=0;
	float m_init_angle=0;
	float m_integral_err=0;
};

#endif  // ArcadeDriving_H
