#include "OI.h"

#include <WPILib.h>

OI::OI() {
	// Process operator interface input here.
	drvStick = new Joystick(0);
	opStick = new Joystick(1);
}
