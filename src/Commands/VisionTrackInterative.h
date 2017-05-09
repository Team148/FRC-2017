#ifndef VisionTrackInterative_H
#define VisionTrackInterative_H

#include "../CommandBase.h"
#include "../Util/VisionServerInterface.h"

class VisionTrackInterative : public CommandBase {
public:
	VisionTrackInterative();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_isFinished;
	VisionServerInterface *m_visionServer;
};

#endif  // VisionTrackInterative_H
