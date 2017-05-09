/*
 * VisionServerInterface.cpp
 *
 *  Created on: May 7, 2017
 *      Author: james_tonthat
 */

#include <Util/VisionServerInterface.h>

VisionServerInterface *VisionServerInterface::m_instance = 0;

bool sortByArea(const RemoteContourReport &lhs, const RemoteContourReport &rhs)	{
	return lhs.Area > rhs.Area;
};

VisionServerInterface::VisionServerInterface() {
	// TODO Auto-generated constructor stub
	m_network_table = NetworkTable::GetTable("GRIP/myContoursReport");
	m_FrameRate = 0;
	m_phc = new PinholeCamera((float)H_CAMERA_RES, (float)V_CAMERA_RES, (float)H_VIEW_ANGLE, (float)V_VIEW_ANGLE, 0, (float)TARGET_HEIGHT);
	m_phc->SetNeutralAxisOffset((float)V_CAMERA_OFFSET);	//camera is pointed up, neutral axis is 36* below neutral
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
	std::vector<double> arr1 = m_network_table->GetNumberArray("area", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr2 = m_network_table->GetNumberArray("centerX", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr3 = m_network_table->GetNumberArray("centerY", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr4 = m_network_table->GetNumberArray("height", llvm::ArrayRef<double>(0.001));
	std::vector<double> arr5 = m_network_table->GetNumberArray("width", llvm::ArrayRef<double>(0.001));

	const unsigned numberOfParticles = 500;

	std::vector<RemoteContourReport> RcRs(numberOfParticles);

	int s1 = arr1.size();
	int s2 = arr2.size();
	int s3 = arr3.size();
	int s4 = arr4.size();
	int s5 = arr5.size();

	if ((s1 > 0) && (s1==s2) && (s1==s3) && (s1==s4) && (s1==s5)) {

		for(unsigned int i = 0; i < arr1.size(); i++)
		{
			RcRs[i].Area = arr1[i];
			RcRs[i].CenterX = arr2[i];
			RcRs[i].CenterY = arr3[i];
			RcRs[i].Height = arr4[i];
			RcRs[i].Width = arr5[i];
		}

		std::sort(RcRs.begin(), RcRs.end(), sortByArea); //Sort the result by Area of target
	}
	//GetTargetValidity();
	int frameRate = (int)NetworkTable::GetTable("GRIP")->GetNumber("FrameRate", 0);
	if(!(m_FrameRate == frameRate))
		m_heartBeat = !m_heartBeat;
	m_FrameRate = frameRate;

}

int VisionServerInterface::GetFrameRate(){
	return m_FrameRate;
}

bool VisionServerInterface::GetHeartBeat(){
	return m_heartBeat;
}

//Takes a sorted contour report vector and checks for target score
bool VisionServerInterface::GetTargetValidity(std::vector<RemoteContourReport>& RcRs){
	if((RcRs[1].Area == 0.0) || (RcRs[1].Width == 0.0)  || (RcRs[1].Height == 0.0))
		return false;
	double arearatio = RcRs[0].Area/RcRs[1].Area;
	double widthratio = RcRs[0].Width/RcRs[1].Width;
	double heightratio = RcRs[0].Height/RcRs[1].Height;
}


