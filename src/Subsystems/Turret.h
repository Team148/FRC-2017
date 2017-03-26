#ifndef Turret_H
#define Turret_H

#include <iostream>
#include <algorithm>
#include <Commands/Subsystem.h>
#include "../RobotMap.h"
#include "CanTalon.h"
#include "Constants.h"
#include "WPIlib.h"



class Turret : public Subsystem {
private:
	//1 CanTalon with integrated encoder feedback
	CANTalon* m_Motor;

	//1 switch for "home" positions.
	DigitalInput* m_HomeSwitch;

	static Turret* m_instance;
	Turret();
	bool m_isClosedLoop = false;
	std::shared_ptr<NetworkTable> m_network_table;
	bool isAutoAiming = false;


public:

	static Turret* GetInstance();
	void InitDefaultCommand();
	void ConfigOpenLoop();
	void ConfigClosedLoop();
	bool IsClosedLoop();

	void SetActualPosition(double position = 0);
	void SetOpen();
	void SetAngle(float angle);
	void SetBigAngle(float angle);
	float GetBigAngle();
	void Reset();
	bool IsHomed();


	void lockTurretAngle(bool lock);
	void UpdateNetworkTable();
	bool IsOnTarget();
	void TargetBoiler(bool isAiming = 0);
	float GetVisionOffset();




};

#endif  // Turret_H
