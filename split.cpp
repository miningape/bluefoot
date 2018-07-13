#include "split.h"
#include <iostream>

using namespace std;

split::split(int atoms) {
	// Set all of our variables
	num_atoms = atoms;
	num_neutrons = 0;

	energyReleased = 0;
}

int split::releaseNeutrons() {
	// Between 1 and 3
	// Average of 2.4
	// Just work with 2
	// Discrete distribution
	// Set no. neutrons released
	if (num_atoms <= 0) {
		return 0;
	}
	else {
		int num_neutrons_released = num_neutrons = 2;
		num_atoms--;
		return num_neutrons_released;
	}
}

int split::releaseByProducts() {
    // The two by products usually Kr-92 and Ba-142
    return 2;
}

void split::calculateEnergyReleasedByOne() {
	// E = mc^2
	// U-236 -> Kr-92 + Ba-142 + 2n
	// LATER: Get the actual masses for different numbers of neutrons
	float deltaM = 0;
	float MeV = 0;
	float energyOfOne = 0;

	deltaM = 236.045563 - (141.919391 + 91.926270 + (num_neutrons * 1.008664));
	MeV = deltaM * 931.5;

	// E = Vq or = eV * 10^6 * Charge of electron
	energyOfOne = MeV * 1000000 * 1.6 * 0.0000000000000000001;

	energyReleased += energyOfOne;
}

float split::getEnergyReleased() {
	return energyReleased;
}

int split::left() {
	return num_atoms;
}

split::~split() {
}
