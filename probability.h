#pragma once
class probabilities
{
public:
    void setProbabilities (int num_molecules, int num_atoms, int num_bad_atoms, int num_byproducts, int Height, float &water, float &atom, float &badAtom, float &byproduct, float &bar, float &nothing);
                 // Calculate
    // Water No. Water atoms
    float waterProbabilities (int num_molecules);
    // Atom No. Atoms
    float atomProbabilities (int num_atoms);
    // Unfissionable // No. Atoms
    float unfissionableProbabilities (int num_bad_atoms);
    // By product // No. Atoms
    float byproductProbabilities (int num_byproducts);
    // Bar // Height
    float barProbabilities (int Height);

    // SET PROBABILITIES
private:
    double totalVolume = 1000000;
};
