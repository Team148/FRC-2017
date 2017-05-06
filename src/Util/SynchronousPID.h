/*
 * SynchronousPID.h
 *
 *  Created on: May 3, 2017
 *      Author: james_tonthat
 */

#ifndef SRC_UTIL_SYNCHRONOUSPID_H_
#define SRC_UTIL_SYNCHRONOUSPID_H_

#include <cmath>

class SynchronousPID {

public:
	SynchronousPID();
	SynchronousPID(double Kp, double Ki, double Kd);
	double calculate(double input);
	void SetP(double Kp);
	void SetI(double Ki);
	void SetD(double Kd);
	void SetPID(double Kp, double Ki, double Kd);
	void SetContinuous(bool continuous);
	void SetDeadband(double deadband);
	void SetSetPoint(double setpoint);
	void SetInputRange(double minimumInput, double maximumInput);
	void SetOutputRange(double minimumOutput, double maximumOutput);

	double GetP();
	double GetI();
	double GetD();
	double Get();
	double GetSetPoint();
	double GetError();

	bool OnTarget(double tolerance);
	void Reset();


private:
    double m_P; // factor for "proportional" control
    double m_I; // factor for "integral" control
    double m_D; // factor for "derivative" control
    double m_maximumOutput = 1.0; // |maximum output|
    double m_minimumOutput = -1.0; // |minimum output|
    double m_maximumInput = 0.0; // maximum input - limit setpoint to
                                         // this
    double m_minimumInput = 0.0; // minimum input - limit setpoint to
                                         // this
    bool m_continuous = false; // do the endpoints wrap around? eg.
                                          // Absolute encoder
    double m_prevError = 0.0; // the prior sensor input (used to compute
                                      // velocity)
    double m_totalError = 0.0; // the sum of the errors for use in the
                                       // integral calc
    double m_setpoint = 0.0;
    double m_error = 0.0;
    double m_result = 0.0;
    double m_last_input;
    double m_deadband = 0.0; // If the absolute error is less than
                                     // deadband
                                     // then treat error for the proportional
                                     // term as 0
};

#endif /* SRC_UTIL_SYNCHRONOUSPID_H_ */
