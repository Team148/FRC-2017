/*
 * FastScheduler.cpp
 *
 *  Created on: May 7, 2017
 *      Author: james_tonthat
 */

#include <Util/FastScheduler.h>
//#include <cmath>
//#include <vector>
//#include "HAL/HAL.h"
#include "Notifier.h"

FastScheduler *FastScheduler::m_instance = 0;


FastScheduler::FastScheduler(double period) {
	m_period = period;
	m_controlLoop = std::make_unique<Notifier>(&FastScheduler::Execute, this);
	m_lastTime = Timer::GetFPGATimestamp();
//	static int instances = 0;
//	instances++;
//	HAL_Report(HALUsageReporting::kResourceType_PIDController, instances);
}

FastScheduler* FastScheduler::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating FastScheduler Class" << std::endl;
		m_instance = new FastScheduler(FAST_SCHEDULER_PERIOD);
	}
	return m_instance;
}

FastScheduler::~FastScheduler() {
	// forcefully stopping the notifier so the callback can successfully run.
	m_controlLoop->Stop();
}

void FastScheduler::Execute(){
	Scheduler::GetInstance()->Run();
	double timeDelta = Timer::GetFPGATimestamp() - m_lastTime;
	std::cout << "Time Delta: " << timeDelta << std::endl;
	m_lastTime = Timer::GetFPGATimestamp();
}

void FastScheduler::Start(){
	m_controlLoop->StartPeriodic(m_period);
}

void FastScheduler::Stop(){
	m_controlLoop->Stop();
}
