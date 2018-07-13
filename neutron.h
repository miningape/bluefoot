#pragma once
class neutrons
{
private:
	int neutronsInChamber;

public:
	neutrons(int released);
	int getNeutrons();
	void editNum_Neutrons(int change);
	~neutrons();
};
