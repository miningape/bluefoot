#include "neutron.h"



neutrons::neutrons(int released) {
	neutronsInChamber = released;
}

int neutrons::getNeutrons() {
	return neutronsInChamber;
}

void neutrons::editNum_Neutrons(int change) {
	neutronsInChamber += change;
}

neutrons::~neutrons()
{
}
