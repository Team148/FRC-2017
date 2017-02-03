#include "Turret.h"

Turret *Turret::m_instance = 0;

Turret::Turret() : Subsystem("Turret") {

}

Turret* Turret::GetInstance() {
	if (m_instance ==  0) {
		std::cout << "info: GetInstance Creating Turret Class" << std::endl;
		m_instance = new Turret();
	}
	return m_instance;
}

void Turret::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}


