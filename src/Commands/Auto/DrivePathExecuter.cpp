#include "DrivePathExecuter.h"

DrivePathExecuter::DrivePathExecuter(double* path) {
	m_path = path;
	m_isFinished = false;
}


void DrivePathExecuter::Initialize() {
	m_startTime = Timer::GetFPGATimestamp();
}


void DrivePathExecuter::Execute() {
}


bool DrivePathExecuter::IsFinished() {
	return m_isFinished;
}


void DrivePathExecuter::End() {

}


void DrivePathExecuter::Interrupted() {

}
