#ifndef DrivePathExecuter_H
#define DrivePathExecuter_H

#include "../../CommandBase.h"
#include "WPILib.h"

class DrivePathExecuter : public CommandBase {
public:
	DrivePathExecuter(double* path);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double *m_path;
	double m_startTime= 0.0;
	bool m_isFinished;
	double m_path_dt;
};

#endif  // DrivePathExecuter_H
