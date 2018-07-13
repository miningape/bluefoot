#pragma once
class split
{
public:
	split(int atoms);
	int releaseNeutrons();
	int releaseByProducts();
	void calculateEnergyReleasedByOne();
	float getEnergyReleased();
	int left();
	~split();

private:
	int num_neutrons;
	int num_byProducts;
	int num_atoms;

	double energyReleased;

};

