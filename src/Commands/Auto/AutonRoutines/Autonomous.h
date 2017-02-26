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
	enum auton
		{
		//	auto naming standards
		//  POSITION_ACTION_ACTION_ACTION...
		//	POSITION_POSITION_ACTION_ACTION...
			BOILER_GEAR_ = 0,
			CENTER_GEAR,
			RETRIEVAL_GEAR,
			BOILER_GEAR_HOPPER_SHOOT
		};
	enum startingSide
	{
		RED = -1,
		BLUE = 1
	};
	int autonSelection = 0;
};

#endif  // Autonomous_H
