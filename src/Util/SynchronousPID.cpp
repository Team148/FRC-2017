/*
 * SynchronousPID.cpp
/**
 * This class implements a PID Control Loop.
 *
 * Does all computation synchronously (i.e. the calculate() function must be
 * called by the user from his own thread)
 *
 * Inspired/Copied from Team254 SynchronousPID.java
 *
 * https://github.com/Team254/FRC-2016-Public/blob/master/src/com/team254/lib/util/SynchronousPID.java
 *
 */


#include <Util/SynchronousPID.h>
#include <cmath>

SynchronousPID::SynchronousPID(){
	m_P = 0.0;
	m_I = 0.0;
	m_D = 0.0;
}


/**
 * Allocate a PID object with the given constants for P, I, D
 *
 * @param Kp
 *            the proportional coefficient
 * @param Ki
 *            the integral coefficient
 * @param Kd
 *            the derivative coefficient
 */
SynchronousPID::SynchronousPID(double Kp, double Ki, double Kd){
	m_P = Kp;
	m_I = Ki;
	m_D = Kd;
}


/**
 * Read the input, calculate the output accordingly, and write to the
 * output. This should be called at a constant rate by the user (ex. in a
 * timed thread)
 *
 * @param input
 *            the input
 */
double SynchronousPID::calculate(double input) {
	m_last_input = input;
	m_error = m_setpoint - input;
	if (m_continuous) {
		if (std::abs(m_error) > (m_maximumInput - m_minimumInput) / 2) {
			if (m_error > 0) {
				m_error = m_error - m_maximumInput + m_minimumInput;
			}
			else {
				m_error = m_error + m_maximumInput - m_minimumInput;
			}
		}
	}

	if ((m_error * m_P < m_maximumOutput) && (m_error * m_P > m_minimumOutput)) {
		m_totalError += m_error;
	}
	else {
		m_totalError = 0;
	}

	// Don't blow away m_error so as to not break derivative
	double proportionalError = std::abs(m_error) < m_deadband ? 0 : m_error;

	m_result = (m_P * proportionalError + m_I * m_totalError + m_D * (m_error - m_prevError));
	m_prevError = m_error;

	if (m_result > m_maximumOutput) {
		m_result = m_maximumOutput;
	} else if (m_result < m_minimumOutput) {
		m_result = m_minimumOutput;
	}
	return m_result;
}

    /**
     * Set the PID controller gain parameters. Set the proportional, integral,
     * and differential coefficients.
     *
     * @param p
     *            Proportional coefficient
     * @param i
     *            Integral coefficient
     * @param d
     *            Differential coefficient
     */
void SynchronousPID::SetPID(double p, double i, double d) {
	m_P = p;
	m_I = i;
	m_D = d;
}

    /**
     * Get the Proportional coefficient
     *
     * @return proportional coefficient
     */
double SynchronousPID::GetP() {
	return m_P;
}

/**
 * Get the Integral coefficient
 *
 * @return integral coefficient
 */
double SynchronousPID::GetI() {
	return m_I;
}

/**
 * Get the Differential coefficient
 *
 * @return differential coefficient
 */
double SynchronousPID::GetD() {
	return m_D;
}

/**
 * Return the current PID result This is always centered on zero and
 * constrained the the max and min outs
 *
 * @return the latest calculated output
 */
double SynchronousPID::Get() {
	return m_result;
}

/**
 * Set the PID controller to consider the input to be continuous, Rather
 * then using the max and min in as constraints, it considers them to be the
 * same point and automatically calculates the shortest route to the
 * setpoint.
 *
 * @param continuous
 *            Set to true turns on continuous, false turns off continuous
 */
void SynchronousPID::SetContinuous(bool continuous) {
	m_continuous = continuous;
}

void SynchronousPID::SetDeadband(double deadband) {
	m_deadband = deadband;
}


/**
 * Set the setpoint for the PID controller
 *
 * @param setpoint
 *            the desired setpoint
 */
void SynchronousPID::SetSetPoint(double setpoint){
	if (m_maximumInput > m_minimumInput) {
			if (setpoint > m_maximumInput) {
				m_setpoint = m_maximumInput;
			} else if (setpoint < m_minimumInput) {
				m_setpoint = m_minimumInput;
			} else {
				m_setpoint = setpoint;
			}
		}
	else {
		m_setpoint = setpoint;
	}
}

/**
 * Sets the maximum and minimum values expected from the input.
 *
 * @param minimumInput
 *            the minimum value expected from the input
 * @param maximumInput
 *            the maximum value expected from the output
 */
void SynchronousPID::SetInputRange(double minimumInput, double maximumInput) {
//	if (minimumInput > maximumInput) {
//		throw new BoundaryException("Lower bound is greater than upper bound");
//	}
	m_minimumInput = minimumInput;
	m_maximumInput = maximumInput;
	SetSetPoint(m_setpoint);
}

/**
 * Returns the current setpoint of the PID controller
 *
 * @return the current setpoint
 */
double SynchronousPID::GetSetPoint() {
	return m_setpoint;
}

/**
 * Returns the current difference of the input from the setpoint
 *
 * @return the current error
 */
double SynchronousPID::GetError() {
	return m_error;
}

/**
 * Return true if the error is within the tolerance
 *
 * @return true if the error is less than the tolerance
 */
bool SynchronousPID::OnTarget(double tolerance) {
	return m_last_input != std::abs(m_last_input - m_setpoint) < tolerance;
}

/**
 * Reset all internal terms.
 */
void SynchronousPID::Reset() {
	m_last_input;
	m_prevError = 0;
	m_totalError = 0;
	m_result = 0;
	m_setpoint = 0;
}



