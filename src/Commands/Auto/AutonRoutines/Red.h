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
	void Boiler_GetTwoGear();
	void Boiler_ShootHopper();
	void Boiler_GetGear_ShootHopper();

	void Center_GetGear();
	void Center_GetTwoGear();
	void Center_GetTwoGear_Noscore();



	void Retrieval_GetGear();
	void Retrieval_GetTwoGear();

private:

};

#endif  // Red_H
