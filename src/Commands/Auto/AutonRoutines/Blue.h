#ifndef Blue_H
#define Blue_H

#include <Commands/CommandGroup.h>

/**
 * The main autonomous command to pickup and deliver the soda to the box.
 */
class Blue: public frc::CommandGroup {
public:
	Blue(int autonSelection);
	void Boiler_GetGear();
	void Boiler_GetTwoGear();
	void Boiler_ShootHopper();
	void Boiler_GetGear_ShootHopper();

	void Center_GetGear();
	void Center_GetTwoGear();


	void Retrieval_GetGear();
	void Retrieval_GetTwoGear();


private:

};

#endif  // Blue_H
