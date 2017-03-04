#include "AutoGearScore.h"
#include "Subsystems/Intake.h"
#include "Commands/Auto/SetIntake.h"
#include "Commands/SetIntakeBall.h"
#include "Commands/Auto/Drive.h"
#include "SetDrivetrainClosedLoop.h"


AutoGearScore::AutoGearScore() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddParallel(new SetDrivetrainClosedLoop(true));
	AddParallel(new SetIntakeBall(0.1));
	AddSequential(new SetIntake(45));
	AddSequential(new Drive(15, 20));
	AddParallel(new SetDrivetrainClosedLoop(false));

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
}
