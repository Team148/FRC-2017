#include "Center1Gear.h"
#include "Commands/Auto/Drive.h"
#include "Commands/Auto/CalibrateArm.h"
#include "Commands/SetIntakeArm.h"
#include "Commands/Auto/SetIntake.h"

Center1Gear::Center1Gear() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	AddParallel(new CalibrateArm());
	AddSequential(new Drive(59,25));
	//AddSequential(new SetIntakeArm(0,2));
	AddSequential(new SetIntake(0));
	AddParallel(new Drive(-25,25));

}
