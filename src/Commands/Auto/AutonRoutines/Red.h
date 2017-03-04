#ifndef Red_H
#define Red_H

#include <Commands/CommandGroup.h>

/**
 * The main autonomous command to pickup and deliver the soda to the box.
 */
class Red: public frc::CommandGroup {
public:
	Red(int autonSelection);
	void Boiler_GetGear();
	void Center_GetGear();
	void Retrieval_GetGear();
	void Retrieval_GetTwoGear();
	void Boiler_GetGear_ShootHopper();

private:
	enum auton
		{
		//	auto naming standards
		//  POSITION_ACTION_ACTION_ACTION...
		//	POSITION_POSITION_ACTION_ACTION...
			BOILER_GEAR_ = 0,
			CENTER_GEAR,
			RETRIEVAL_GEAR,
			RETRIEVAL_TWOGEAR,
			BOILER_GEAR_HOPPER_SHOOT
		};
};

#endif  // Red_H
