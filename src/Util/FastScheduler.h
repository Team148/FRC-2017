/*
 * FastScheduler.h
 *
 *  Created on: May 7, 2017
 *      Author: james_tonthat
 */

#ifndef SRC_UTIL_FASTSCHEDULER_H_
#define SRC_UTIL_FASTSCHEDULER_H_

#pragma once

//#include <atomic>
//#include <memory>
//#include <queue>
//#include <string>
#include <iostream>
#include "Base.h"
//#include "Controller.h"
//#include "HAL/cpp/priority_mutex.h"
//#include "LiveWindow/LiveWindow.h"
#include "Notifier.h"
//#include "Timer.h"
#include <Commands/Scheduler.h>
#include "../Constants.h"
#include "WPILib.h"

class FastScheduler {
public:
	static FastScheduler* GetInstance();
	virtual ~FastScheduler();
	void Start();
	void Stop();

private:
	FastScheduler(double period);
	static FastScheduler *m_instance;
	double m_lastTime = 0;

protected:
	double m_period;

//	std::shared_ptr<ITable> m_table;
	void Execute();


//	mutable priority_recursive_mutex m_mutex;

	std::unique_ptr<Notifier> m_controlLoop;
};

#endif /* SRC_UTIL_FASTSCHEDULER_H_ */
