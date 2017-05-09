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
#include <vector>
#include "../Subsystems/Turret.h"
#include "PinholeCamera.h"

struct RemoteContourReport {
	double Area;
	double CenterX;
	double CenterY;
	double Height;
	double Width;
};

//Structure to represent the scores for the various tests used for target identification
struct RemoteScores {
	double Area;
	double Aspect;
};



class VisionServerInterface {

//A structure to hold contour measurements a particle

public:

	static VisionServerInterface* GetInstance();
	int GetFrameRate();
	bool GetHeartBeat();
	float GetYawDegrees();
	float GetDistanceInches();

private:
	static VisionServerInterface *m_instance;
	VisionServerInterface();
	int m_FrameRate;
	bool m_heartBeat = false;
	std::shared_ptr<NetworkTable> m_network_table;
	void Update();
	PinholeCamera *m_phc;
	bool GetTargetValidity(std::vector<RemoteContourReport>& RcRs);

};

#endif /* SRC_UTIL_VISIONSERVERINTERFACE_H_ */
