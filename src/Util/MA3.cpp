/*
 * MA3.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: justingriggs
 */

#include <Util/MA3.h>


MA3::MA3(int port) {
	m_analogInput = new AnalogInput(port);
	m_analogInput->SetAverageBits(6);
	Reset();
}

//Returns the angle relative to the zeropoint, currently doesn't support rollover
double MA3::GetCalibratedAngle() {
	double currentangle = GetRawAngle();
	m_prevangle = currentangle;
	return m_zeropointangle - currentangle;

}


//Reset the Encoder to set the Zero point to the current angle.
void MA3::Reset() {
	m_num_rotations = 0;
	double calval = m_analogInput->GetAverageVoltage();
	m_zeropointangle = GetRawAngle();
	m_prevval = calval;
	m_prevangle = GetRawAngle();
}

//Returns the current voltage (0-5V)
double MA3::GetRawVoltage() {
	return m_analogInput->GetVoltage();
}

//returns angle in radians
double MA3::GetRawAngle() {
	return 2 * M_PI * m_analogInput->GetVoltage() / 5.0;
}
