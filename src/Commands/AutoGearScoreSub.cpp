#include <Commands/Auto/IntakeAutoGearScore.h>
#include <Commands/AutoGearScoreSub.h>
#include "Subsystems/Intake.h"
#include "Commands/Auto/SetIntake.h"
#include "Commands/SetIntakeBall.h"
#include "Commands/SetIntakeGear.h"
#include "Commands/Auto/Drive.h"
#include "SetDrivetrainClosedLoop.h"



AutoGearScoreSub::AutoGearScoreSub() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddSequential(new SetDrivetrainClosedLoop(true));
	AddParallel(new IntakeAutoGearScore());
	//AddSequential(new SetIntake(INTAKE_ARM_POSITION_UP/2));
	AddSequential(new Drive(-20, 25));
	AddSequential(new SetDrivetrainClosedLoop(false));



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
