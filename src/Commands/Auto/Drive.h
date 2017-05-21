#ifndef Drive_H
#define Drive_H

#include "../../CommandBase.h"
#include <queue>
#include "math.h"
#include "util/Logger.h"


using namespace std;
class Drive : public CommandBase {
public:
	Drive(double inches, double velocity);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	Logger *log;

private:
	float m_travelDistance;
	float m_cruiseVelocity;
	bool m_isFinished=0;
	float m_initangle = 0;
	bool m_isReverse = false;

	//drivetrain constraints
	float m_maxAccelRate = 100; 		//Inches per sec^2
	float m_maxDecelRate= 90;		//Inches per sec^2
	float m_maxdrivevelocity = 150; //Inches per se
	float m_dt = 0.02;				//time step set to 20ms(50Hz).
	queue <float> m_velocity;
	queue <float> m_distance;
};

#endif  // Drive_H
