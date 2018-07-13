#include "probability.h"
#include <iostream>
#include <windows.h>

using namespace std;

void probabilities::setProbabilities (int num_molecules, int num_atoms, int num_bad_atoms, int num_byproducts, int Height, float &water, float &atom, float &badAtom, float &byproduct, float &bar, float &nothing) {
    water = waterProbabilities(num_molecules);
    atom = atomProbabilities(num_atoms);
    badAtom = unfissionableProbabilities(num_bad_atoms);
    byproduct = byproductProbabilities(num_byproducts);
    bar = barProbabilities(Height);

    if (bar > 0) {
        water *= ((100-bar)/100);
        atom *= ((100-bar)/100);
        badAtom *= ((100-bar)/100);
        byproduct *= ((100-bar)/100);
    }

    nothing = 100 - (water + atom + badAtom + byproduct + bar);
}

float probabilities::waterProbabilities (int num_molecules) {
    double size_of_water_molecule = 2.99; // 0.0299
    return ((num_molecules * size_of_water_molecule) / totalVolume) * 100;
}

float probabilities::atomProbabilities (int num_atoms) {
    double size_of_atom = 20.5; // 0.205
    return ((num_atoms * size_of_atom) / totalVolume) * 100;
}

float probabilities::unfissionableProbabilities (int num_bad_atoms) {
    double size_of_bad_atom = 20.5; // 0.205
    return ((num_bad_atoms * size_of_bad_atom) / totalVolume) * 100;
}

float probabilities::byproductProbabilities (int num_byproducts) {
    double size_of_byproduct = 2.9; // 0.029
    return ((num_byproducts * size_of_byproduct) / totalVolume) * 100;
}

float probabilities::barProbabilities (int Height) {
    return Height;
}
