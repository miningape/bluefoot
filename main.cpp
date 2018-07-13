#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include <math.h>
#include <Windows.h>
#include <conio.h>

#include "split.h"
#include "travelling.h"
#include "neutron.h"
#include "probability.h"

using namespace std;

void loadValues(float &water, float &atom, float &bar, float &nothing, float &unfissionable, float &byproduct, int &num_atoms_start, int &num_neutrons_start, int &barHeight);
void setValues(float water, float atom, float bar, float nothing, float unfissionable, float byproduct, int num_atoms_start, int num_neutrons_start, int barHeight);

int main() {
    //vector<float> averagevector;
    //for (int t = 0; t < 5; t++) {
    vector<float> averageholder;

	// Variable set up
	float waterHitChance,
		atomHitChance,
		barHitChance,
		nothingChance,
		unfissionableChance,
		byproductChance;

    int num_atoms_start,
		num_neutrons_start,
		barHeight;

	double numFissions;
	float composition = 0.7/100;
	int nonFissionableAtoms = 0;
	int num_byproducts = 0;

	float fastHolder;

	loadValues(waterHitChance, atomHitChance, barHitChance, nothingChance, unfissionableChance, byproductChance, num_atoms_start, num_neutrons_start, barHeight);

	int num_water_molecules = num_atoms_start * 10;

	nonFissionableAtoms = num_atoms_start;
	num_atoms_start = num_atoms_start * 0.1;
	//float ratioA = num_atoms_start / nonFissionableAtoms;
    cout << num_atoms_start << endl;
	nonFissionableAtoms -= num_atoms_start;



	probabilities inPercent;

	// Set the probabilities
    inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);

	setValues(waterHitChance, atomHitChance, barHitChance, nothingChance, unfissionableChance, byproductChance, num_atoms_start, num_neutrons_start, barHeight);


		cout << "Water:\t\t" << waterHitChance << "%\nAtom:\t\t" << atomHitChance << "%\nBar:\t\t" << barHitChance << "%\nMissed:\t\t" << nothingChance << "%\nUnfissionable:\t\t" << unfissionableChance << "%\nBy product:\t\t" << byproductChance << "%\n\nStarting number of atoms: \t" << num_atoms_start << "\nStarting number of neutrons: \t" << num_neutrons_start << endl;
		system("pause");
		system("cls");



	// Starting reaction
	int numCycles = 0;
	int waterNeutronCount = 0, waterNeutronsAdded = 0, waterNeutronsRemoved = 0, nextRoundWaterNeutrons = 0; // Var to keep track of how many neutrons have hit water
	int neutronsAdded = 0, neutronsRemoved = 0;

	// Concentration calculation


    // Beginning the reaction
	split		uraniumAtoms(num_atoms_start);
	neutrons	inChamber(num_neutrons_start);
	travelling	neutron;

	neutron.setProbabilities(waterHitChance, atomHitChance, barHitChance, nothingChance, unfissionableChance, byproductChance);

	do {

		inChamber.editNum_Neutrons(neutronsAdded - neutronsRemoved);
		neutronsAdded = neutronsRemoved = 0;

		waterNeutronCount = waterNeutronsAdded - waterNeutronsRemoved;
		waterNeutronsAdded = nextRoundWaterNeutrons = 0;

		numFissions = 0;

		// Run encounters for every normal neutron
		for (int i = 0; i < inChamber.getNeutrons(); i++) {
			// cout << "Neutron: " << i+1 << " of " << inChamber.getNeutrons() << endl;
			// Run the encounters for the slowed neutrons first, then work with the non slowed one, because there will always be the same amount or less slowed neutrons than regular neutrons, because the slowed ones come from the regular ones and have a 20% chance for success
			if (waterNeutronCount > 0) {
				// Change probabilities
				//neutron.makeProbabilities() // PASS BY REFERENCE TO CHANGE THE VALUE
                // Remove the water neutron from this round
                waterNeutronCount--;
				//inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);
				//neutron.setProbabilities(0, atomHitChance + 70, barHitChance, nothingChance - 40, unfissionableChance - 10, byproductChance);
                neutron.setProbabilities(0, 100, 0, 0, 0, 0);
			}
			else {
                inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);
				neutron.setProbabilities(waterHitChance, atomHitChance, barHitChance, nothingChance, unfissionableChance, byproductChance);
			}

			// Routine to calculate the average every 10 neutrons
			// Average of 10


			// Get random number for the current neutron
			neutron.randomNumber(0, 99);

			// Chance of hitting water
			if (neutron.hitsWater()) {
				if (waterNeutronCount > 0) {
					// Water Neutron is actually lost
					// No need to remove here, because it is already gone
					continue;
				}
				else {
					waterNeutronsAdded++;
					continue;
				}
			}

			// Chance of hitting an atom
			if (neutron.hitsAtom()) {
				// Release neutrons
				neutronsAdded += (uraniumAtoms.releaseNeutrons() - 1); // To account for the neutron absorbed by the nucleus
                num_byproducts += uraniumAtoms.releaseByProducts();
				// Release energy
				uraniumAtoms.calculateEnergyReleasedByOne();

				numFissions++;

				continue;
			}

			// Chance of hitting the bar
			if (neutron.hitsBar()) {
				// Neutron gets removed
				neutronsRemoved++;

				continue;
			}

			// Chance of hitting nothing
			if (neutron.doesNothing()) {
				// Nothing happens
				continue;
			}

			if (neutron.hitsUnfissionable()) {
                // Neutron gets removed
                neutronsRemoved++;

                continue;
			}

			if (neutron.hitsByproduct()) {
                // Neutron gets removed
                neutronsRemoved++;

                continue;
			}
		}
		numCycles++;

		// Print information routine
		system("cls");

		// Current state of the reactor
		cout << "Atoms left: " << uraniumAtoms.left() << "\t\tNeutrons left: " << inChamber.getNeutrons() << endl << "Some number" << "/" << inChamber.getNeutrons() << "\t\tThe number of cycles: " << numCycles << endl;

		cout << endl;

        fastHolder = (numFissions / inChamber.getNeutrons());

		cout << "Fissions per Neutron:\t" << fastHolder << /*" fissions/neutron => " << forAverage << */endl;

		if (!(inChamber.getNeutrons() == 0)) {
            averageholder.push_back(fastHolder);
		}

		cout << "Fissions per Atom:\t" << (numFissions / uraniumAtoms.left()) << " fissions/atom" << endl;

		cout << endl;

		// Energy Released
		cout << uraniumAtoms.getEnergyReleased() << " J in " << numCycles << " cycles" << endl << "Power: " << uraniumAtoms.getEnergyReleased() / numCycles << endl;

		cout << endl;

		// Percentage chance of things happening
		cout << "Water:\t\t" << waterHitChance << "%\nAtom:\t\t" << atomHitChance << "%\nBar:\t\t" << barHitChance << "%\nMissed:\t\t" << nothingChance << "%\nUnfissionable:\t" << unfissionableChance << "%\nBy product:\t" << byproductChance << "%\n\nStarting number of atoms: \t" << num_atoms_start << "\nStarting number of neutrons: \t" << num_neutrons_start << endl;

		cout << endl;

		// Bar height
		cout << "Bar height: " << barHeight << endl;

		// Check for input to update data
		if (_kbhit()) {
			char buttonPressed = _getch();
			switch (buttonPressed){
            // Raising control bars
            case 'r':
                barHeight -= 1;

                inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);
                setValues(waterHitChance, atomHitChance, barHitChance, nothingChance, unfissionableChance, byproductChance, num_atoms_start, num_neutrons_start, barHeight);
                // loadValues(waterHitChance, atomHitChance, barHitChance, nothingChance, unfissionableChance, byproductChance, num_atoms_start, num_neutrons_start, barHeight);
                break;

            // Lowering control bars
            case 'f':
                barHeight += 1;

                inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);
                setValues(waterHitChance, atomHitChance, barHitChance, nothingChance, byproductChance, unfissionableChance, num_atoms_start, num_neutrons_start, barHeight);
                // loadValues(waterHitChance, atomHitChance, barHitChance, nothingChance, byproductChance, unfissionableChance, num_atoms_start, num_neutrons_start, barHeight);
                break;

            case 'e':
                barHeight = 100;

                inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);
                setValues(waterHitChance, atomHitChance, barHitChance, nothingChance, byproductChance, unfissionableChance, num_atoms_start, num_neutrons_start, barHeight);
                break;
            }
		}

	} while (inChamber.getNeutrons() > 0 && uraniumAtoms.left() > 0);

	//whileAverage = accumulate(fissionsPerNeutronWhileHolder.begin(), fissionsPerNeutronWhileHolder.end(), 0) / fissionsPerNeutronWhileHolder.size();



	float average = accumulate(averageholder.begin(), averageholder.end(), 0.0) / averageholder.size();
    float maxi = *max_element(averageholder.begin(), averageholder.end());
    float mini = *min_element(averageholder.begin(), averageholder.end());

	cout << "Median Fissions per Neutron:\t\t" << average << "\nRange of Fissions per neutron:\t\t" << mini << "-" << maxi << endl;

	//averagevector.push_back(average);

	barHeight = 0;

    inPercent.setProbabilities(num_water_molecules, num_atoms_start, nonFissionableAtoms, num_byproducts, barHeight, waterHitChance, atomHitChance, unfissionableChance, byproductChance, barHitChance, nothingChance);
    setValues(waterHitChance, atomHitChance, barHitChance, nothingChance, byproductChance, unfissionableChance, num_atoms_start, num_neutrons_start, barHeight);
    //}

    /*for (int t = 0; t < 5; t++) {
        cout << t << ": " << averagevector[t] << endl;
    }*/

	return 0;
}

void loadValues(float &water, float &atom, float &bar, float &nothing, float &unfissionable, float &byproduct, int &num_atoms_start, int &num_neutrons_start, int &barHeight) {
	// File reading routine
	ifstream inputFile;

	string	Line1, // water
			Line2, // atom
			Line3, // bar
			Line4, // nothing
			Line5, // unfissionable
			Line6, // by product
			Line7, // starting atoms
			Line8, // starting neutrons
			Line9; // bar height

	string value;

	inputFile.open("data.txt");

		// Getting each line data
		getline(inputFile, Line1, '\n');
		getline(inputFile, Line2, '\n');
		getline(inputFile, Line3, '\n');
		getline(inputFile, Line4, '\n');
		getline(inputFile, Line5, '\n');
		getline(inputFile, Line6, '\n');
		getline(inputFile, Line7, '\n');
		getline(inputFile, Line8, '\n');
		getline(inputFile, Line9, '\n');

		// Handling line 1 (Water Hit Chance)
		value = Line1.substr(Line1.find(":") + 2, Line1.find(","));
		water = atoi(value.c_str());

		// Handling line 2 (Atom Hit Chance)
		value = Line2.substr(Line2.find(":") + 2, Line2.find(","));
		atom = atoi(value.c_str());

		// Handling line 3 (Bar Hit Chance)
		value = Line3.substr(Line3.find(":") + 2, Line3.find(","));
		bar = atoi(value.c_str());

		// Handling line 4 (Miss Chance)
		value = Line4.substr(Line4.find(":") + 2, Line4.find(","));
		nothing = atoi(value.c_str());

		// Handling line 5 (unfissionable)
		value = Line5.substr(Line5.find(":") + 2, Line5.find(","));
		unfissionable = atoi(value.c_str());

		// Handling line 6 (byproduct Chance)
		value = Line6.substr(Line6.find(":") + 2, Line6.find(","));
		byproduct = atoi(value.c_str());

		// Handling line 7 (Number of starting atoms)
		value = Line7.substr(Line7.find(":") + 2, Line7.find(","));
		num_atoms_start = atoi(value.c_str());

		// Handling line 7 (Number of starting neutrons)
		value = Line8.substr(Line8.find(":") + 2, Line8.find(","));
		num_neutrons_start = atoi(value.c_str());

		// Handling line 8 (Bar height)
		value = Line9.substr(Line9.find(":") + 2, Line9.find(","));
		barHeight = atoi(value.c_str());

		// Done loading vars

	// Closing the file
	inputFile.close();
}

void setValues(float water, float atom, float bar, float nothing, float unfissionable, float byproduct, int num_atoms_start, int num_neutrons_start, int barHeight) {
    ofstream outputFile;

    outputFile.open("data.txt");

    if (outputFile.is_open()){
        outputFile << "%Chance of hitting a water molecule	: " << water << ",\n";
        outputFile << "%Chance of hitting a Uranium atom	: " << atom << ",\n";
        outputFile << "%Chance of hitting the control bars	: " << bar << ",\n";
        outputFile << "%Chance of doing nothing		: " << nothing << ",\n";
        outputFile << "%Chance of hitting an unfissionable atom		: " << unfissionable << ",\n";
        outputFile << "%Chance of hitting a by product		: " << byproduct << ",\n";
        outputFile << "Starting number of Uranium atoms	: " << 10000 << ",\n";
        outputFile << "Starting number of neutrons		: " << num_neutrons_start << ",\n";
        outputFile << "Height of the control bars		: " << barHeight << ",\n";
    } else {
        // 13 Means the write file wont open
        system("cls");
        cout << "Failed to open the file for writing" << endl;
        system("Pause");
    }

    outputFile.close();
}
