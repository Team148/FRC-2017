#ifndef Autonomous_H
#define Autonomous_H

#include <Commands/CommandGroup.h>

/**
 * The main autonomous command to pickup and deliver the soda to the box.
 */
class Autonomous: public frc::CommandGroup {
public:
	Autonomous(bool red, int getGears, bool isShooting, bool getHopper);

private:

	int autonSelection = 0;
};

#endif  // Autonomous_H
