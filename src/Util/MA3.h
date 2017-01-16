/*
 * MA3.h
 *
 *  Created on: Oct 19, 2016
 *      Author: justingriggs
 */

#ifndef SRC_SUBSYSTEMS_MA3_H_
#define SRC_SUBSYSTEMS_MA3_H_

#include "WPILib.h"
#include "math.h"

class MA3 {
public:
	MA3(int port);

	void Reset();
	double GetRawVoltage();
	double GetRawAngle();
	double GetCalibratedAngle();

private:
	int m_num_rotations = 0;
	AnalogInput* m_analogInput;
	double m_zeropointangle;
	double m_accumulatedangle;
	double m_prevval;
	double m_prevangle = 0;

};


#endif /* SRC_SUBSYSTEMS_MA3_H_ */
