/*
 * VisionServerInterface.h
 *
 *  Created on: May 7, 2017
 *      Author: james_tonthat
 */

#ifndef SRC_UTIL_VISIONSERVERINTERFACE_H_
#define SRC_UTIL_VISIONSERVERINTERFACE_H_

#include <iostream>
#include "WPIlib.h"
#include "../Constants.h"

class VisionServerInterface {
public:
	static VisionServerInterface* GetInstance();
	int GetFrameRate();
	bool GetHeartBeat();
private:
	static VisionServerInterface *m_instance;
	VisionServerInterface();
	int m_FrameRate;
	bool m_heartBeat = false;
	std::shared_ptr<NetworkTable> m_network_table;
	void Update();
	int UpdateFrameRate();
};

#endif /* SRC_UTIL_VISIONSERVERINTERFACE_H_ */
