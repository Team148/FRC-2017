/*
 * VisionServerInterface.cpp
 *
 *  Created on: May 7, 2017
 *      Author: james_tonthat
 */

#include <Util/VisionServerInterface.h>

VisionServerInterface *VisionServerInterface::m_instance = 0;

VisionServerInterface::VisionServerInterface() {
	// TODO Auto-generated constructor stub
	m_network_table = NetworkTable::GetTable("GRIP/myContoursReport");
	m_FrameRate = (int)m_network_table->GetNumber("FrameRate", 0);

}
VisionServerInterface* VisionServerInterface::GetInstance(){
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating VisionServerInterface Class" << std::endl;
		m_instance = new VisionServerInterface();
	}
	return m_instance;
}

void VisionServerInterface::Update(){
	m_network_table = NetworkTable::GetTable("GRIP/myContoursReport");
	int frameRate = (int)m_network_table->GetNumber("FrameRate", 0);

	if(!(m_FrameRate == frameRate))
		m_heartBeat = !m_heartBeat;
	m_FrameRate = frameRate;

}

int VisionServerInterface::UpdateFrameRate(){
	return m_FrameRate;
}

bool VisionServerInterface::GetHeartBeat(){
	return m_heartBeat;
}
