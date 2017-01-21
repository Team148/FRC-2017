#include "OI.h"

#include <WPILib.h>

OI::OI() {

	std::cout << "info: creating operator interface." << std::endl;

	drvStick = new Joystick(0);
	m_drvButton1 = new JoystickButton(drvStick, 1);
	m_drvButton2 = new JoystickButton(drvStick, 2);
	m_drvButton3 = new JoystickButton(drvStick, 3);
	m_drvButton4 = new JoystickButton(drvStick, 4);
	m_drvButton5 = new JoystickButton(drvStick, 5);
	m_drvButton6 = new JoystickButton(drvStick, 6);
	m_drvButton7 = new JoystickButton(drvStick, 7);
	m_drvButton8 = new JoystickButton(drvStick, 8);


	opStick = new Joystick(1);
	m_opButton1 = new JoystickButton(opStick, 1);
	m_opButton2 = new JoystickButton(opStick, 2);
	m_opButton3 = new JoystickButton(opStick, 3);
	m_opButton4 = new JoystickButton(opStick, 4);
	m_opButton5 = new JoystickButton(opStick, 5);
	m_opButton6 = new JoystickButton(opStick, 6);
}


int OI::GetSelectorA() {
	if(m_brickAselect1->Get())
		return 1;
	if(m_brickAselect2->Get())
		return 2;
	if(m_brickAselect3->Get())
		return 3;
	if(m_brickAselect4->Get())
		return 4;
	if(m_brickAselect5->Get())
		return 5;
	if(m_brickAselect6->Get())
		return 6;
	if(m_brickAselect7->Get())
		return 7;
	if(m_brickAselect8->Get())
		return 8;

	return 0;
}


int OI::GetSelectorB() {
	if(m_brickBselect1->Get())
		return 1;
	if(m_brickBselect2->Get())
		return 2;
	if(m_brickBselect3->Get())
		return 3;
	if(m_brickBselect4->Get())
		return 4;
	if(m_brickBselect5->Get())
		return 5;
	if(m_brickBselect6->Get())
		return 6;
	if(m_brickBselect7->Get())
		return 7;
	if(m_brickBselect8->Get())
		return 8;

	return 0;
}


int OI::GetDSSwitches() {
	int switches = 0;
	int sw1 = m_dsiSw1->Get();
	switches = sw1;
	int sw2 = m_dsiSw2->Get();
	switches = switches + (sw2 << 1);
	int sw3 = m_dsiSw3->Get();
	switches = switches + (sw3 << 2);
	int sw4 = m_dsiSw4->Get();
	switches = switches + (sw4 << 3);
	int sw5 = m_dsiSw5->Get();
	switches = switches + (sw5 << 4);

	return switches;
}


bool OI::GetSw1() {
	return m_dsiSw1->Get();
}


bool OI::GetSw2() {
	return m_dsiSw2->Get();
}


bool OI::GetSw3() {
	return m_dsiSw3->Get();
}


bool OI::GetSw4() {
	return m_dsiSw4->Get();
}


bool OI::GetSw5() {
	return m_dsiSw5->Get();
}
