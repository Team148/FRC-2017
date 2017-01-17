#ifndef OI_H
#define OI_H
#include "WPILib.h"

class OI {
public:
	OI();

	Joystick* drvStick;
	Joystick* opStick;
	Joystick* dsiBrickA;
	Joystick* dsiBrickB;

	int GetSelectorA();
	int GetSelectorB();
	int GetDSSwitches();

	bool GetSw1();
	bool GetSw2();
	bool GetSw3();
	bool GetSw4();
	bool GetSw5();

private:


	JoystickButton* m_brickAselect1;
	JoystickButton* m_brickAselect2;
	JoystickButton* m_brickAselect3;
	JoystickButton* m_brickAselect4;
	JoystickButton* m_brickAselect5;
	JoystickButton* m_brickAselect6;
	JoystickButton* m_brickAselect7;
	JoystickButton* m_brickAselect8;

	JoystickButton* m_brickBselect1;
	JoystickButton* m_brickBselect2;
	JoystickButton* m_brickBselect3;
	JoystickButton* m_brickBselect4;
	JoystickButton* m_brickBselect5;
	JoystickButton* m_brickBselect6;
	JoystickButton* m_brickBselect7;
	JoystickButton* m_brickBselect8;

	JoystickButton* m_dsiSw1;
	JoystickButton* m_dsiSw2;
	JoystickButton* m_dsiSw3;
	JoystickButton* m_dsiSw4;
	JoystickButton* m_dsiSw5;
};

#endif  // OI_H
