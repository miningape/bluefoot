#include "travelling.h"


travelling::travelling()
{

}

void travelling::randomNumber(int min, int max) {
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	mt19937 generator(seed);
	uniform_real_distribution<float> distribution(min, max);

	currentRandomNumber = distribution(generator);
}

void travelling::setProbabilities(float water, float atom, float bar, float miss, float unfissionable, float byproduct)
{
    // BASED on the number of particles
    // in a 9m^3 chamber filled with water
    // density * volume = num particles
    // (num particles * size of 1 particle) / volume = probability of hitting
    // 1 - all the other probabilities = loat probabilities
	hitWaterBetween = { 0, water };
	hitAtomBetween = { water, (water + atom) };
	hitBarBetween = { (water + atom), (water + atom + bar) };
	missBetween = { (water + atom + bar), (water + atom + bar + miss) };
	unfissionableBetween = { (water + atom + bar + miss), (water + atom + bar + miss + unfissionable) };
	byproductBetween = { (water + atom + bar + miss + unfissionable), (water + atom + bar + miss + unfissionable + byproduct) };
}

bool travelling::hitsWater()
{
	if (currentRandomNumber >= hitWaterBetween[0] && currentRandomNumber < hitWaterBetween[1])
		return true;
	else
		return false;
}

bool travelling::hitsAtom()
{
	if (currentRandomNumber >= hitAtomBetween[0] && currentRandomNumber < hitAtomBetween[1])
		return true;
	else
		return false;
}

bool travelling::hitsBar()
{
	if (currentRandomNumber >= hitBarBetween[0] && currentRandomNumber < hitBarBetween[1])
		return true;
	else
		return false;
}

bool travelling::doesNothing()
{
	if (currentRandomNumber >= missBetween[0] && currentRandomNumber < missBetween[1])
		return true;
	else
		return false;
}

bool travelling::hitsUnfissionable()
{
	if (currentRandomNumber >= unfissionableBetween[0] && currentRandomNumber < unfissionableBetween[1])
		return true;
	else
		return false;
}

bool travelling::hitsByproduct()
{
    if (currentRandomNumber >= byproductBetween[0] && currentRandomNumber < byproductBetween[1])
        return true;
    else
        return false;
}

travelling::~travelling()
{
}
