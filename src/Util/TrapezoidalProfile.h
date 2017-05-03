/*
 * TrapezoidalProfile.h
 *
 *  Created on: Oct 20, 2016
 *      Author: james_tonthat
 */

#ifndef SRC_NAV_TRAPEZOIDALPROFILE_H_
#define SRC_NAV_TRAPEZOIDALPROFILE_H_

#include <math.h>

class TrapezoidalProfile {
public:
	TrapezoidalProfile(double MaxVel, double MaxAccel, double MaxDecel);
	double GetVelocity();
	double GetAcceleration();
	double GetPosition();
	void SetVelocity(double CurrentVel);
	void SetAcceleration(double CurrentAccel);
	void SetPosition(double CurrentPos);
	void Reset();
	void UpdateKinematics(double Accel, double dt);
	void Update(double ActualDistance, double ActualVel, double GoalVel, double dt);
	void PrintAccelProfile();

private:
	class AccelerationProfile {
	public:
		AccelerationProfile();
		double m_StartAccel;
		double m_StartTime;
		double m_ConstTime;
		double m_EndAccel;
		double m_EndTime;
	};
	void GenerateAccelProfile(double ActualDistance, double ActualVel, double GoalVel);
	double m_CurrentAccel;
	double m_CurrentVel;
	double m_CurrentPos;
	double m_MaxVel;
	double m_MaxAccel;
	double m_MaxDecel;

	AccelerationProfile *profile;
};

#endif /* SRC_NAV_TRAPEZOIDALPROFILE_H_ */
