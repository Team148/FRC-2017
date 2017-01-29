#ifndef Drive_H
#define Drive_H

#include "../../CommandBase.h"
#include <queue>
#include "math.h"

using namespace std;
class Drive : public CommandBase {
public:
	Drive(double inches, double velocity);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float m_travelDistance;
	float m_cruiseVelocity;
	bool m_isFinished=0;

	//drivetrain constraints
	float m_maxAccelRate = 80; 		//Inches per sec^2
	float m_maxdrivevelocity = 200; //Inches per sec
	float m_dt = 0.02;				//time step set to 20ms(50Hz).
	queue <float> m_output;
};

#endif  // Drive_H
