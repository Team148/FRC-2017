#ifndef FeedShooter_H
#define FeedShooter_H

#include "Commands/InstantCommand.h"

class FeedShooter : public InstantCommand {
public:
	FeedShooter(bool on);
	void Initialize();
private:
	bool m_on = false;
	double m_voltage = 0.0;
};

#endif  // FeedShooter_H
