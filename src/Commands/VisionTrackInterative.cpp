#include "VisionTrackInterative.h"

VisionTrackInterative::VisionTrackInterative() {
	m_visionServer = VisionServerInterface::GetInstance();
	Requires(Turret::GetInstance());
	Requires(Shooter::GetInstance());
	m_isFinished = false;
	SetTimeout(2.0);
}


void VisionTrackInterative::Initialize() {

}


void VisionTrackInterative::Execute() {

}


bool VisionTrackInterative::IsFinished() {
	return false;
}


void VisionTrackInterative::End() {

}

void VisionTrackInterative::Interrupted() {

}
