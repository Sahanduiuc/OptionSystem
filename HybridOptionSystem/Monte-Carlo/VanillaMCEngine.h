#pragma once
#include "vanillaengine.h"
#include "Random2.h"
#include "minmax.h"



class VanillaMCEngine : public VanillaEngine
{
public:

	VanillaMCEngine(const Wrapper<VanillaOption>& TheProduct_,
		const Parameters& R_,
		const Parameters& Vol_,
		const Wrapper<RandomBase>& TheGenerator_,
		double Spot_,
		int n_steps_);

	virtual void GetOnePath(double& SpotValues);
	virtual ~VanillaMCEngine() {}


private:
	double spot;
	double movedSpot;
	double rootVariance;
	int n_steps;
	double expiry;
	Parameters r;
	Parameters vol;
	Wrapper<RandomBase> TheGenerator;
	MJArray Variaterray;
};