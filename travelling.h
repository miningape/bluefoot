using namespace std;
#pragma once
#include <random>
#include <chrono>
class travelling {
public:
	travelling();
	void randomNumber(int max, int min);
	void setProbabilities(float water, float atom, float bar, float miss, float unfissionable, float byproducts);
	bool hitsWater();
	bool hitsAtom();
	bool hitsBar();
	bool doesNothing();
	bool hitsUnfissionable();
	bool hitsByproduct();
	~travelling();

private:
	int currentRandomNumber = 0;
	vector<float> hitWaterBetween;
	vector<float> hitAtomBetween;
	vector<float> hitBarBetween;
	vector<float> missBetween;
	vector<float> unfissionableBetween;
	vector<float> byproductBetween;
};

