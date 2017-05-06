#ifndef DriveStraightTMP_H
#define DriveStraightTMP_H

#include "../../CommandBase.h"
#include "Util/TrapezoidalProfile.h"
#include "./Constants.h"
#include "WPILib.h"
#include <math.h>
#include <iostream>
#include "Util/SynchronousPID.h"

class DriveStraightTMP : public CommandBase {
public:
	DriveStraightTMP(double distance, double velocity, double endVelocity = 0.0,
					double positionTolerance = 1.0, double timeOut = 0.0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	void CurrentState();
private:
	bool m_isFinished = false;
	double m_startTime = 0.0;
	double m_startPosition = 0.0;
	double m_endPosition = 0.0;
	double m_lastTime = 0.0;
	//double m_currentTime = 0.0;
	double m_endVelocity;
	double m_positionTolerance;
	double m_initAngle;

	TrapezoidalProfile *m_profile;
	SynchronousPID *m_PID;
};

#endif  // DriveStraightTMP_H
