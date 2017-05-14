#include "VanillaMCEngine.h"
#include <cmath>

// Use the gaussian number to simulate a spot value
void VanillaMCEngine::GetOnePath(double& SpotValues)
{
	TheGenerator->GetGaussians(Variaterray);
	double dt = expiry / n_steps;
	double variance = vol.IntegralSquare(0, dt);
	double drift = r.Integral(0, dt);
	double itoCorrection = -0.5*variance;
	double minSpot = spot;
	double maxSpot = spot;
	double Spot_1 = spot;
	double Spot_2;
	rootVariance = sqrt(variance);
	//For geometric brownian motion
	//ST=St*exp( integral(t,T,r(u)-sigma(u)**2,du) + integral(t,T,sigma(u),dW(u)) )
	//Euler Scheme1: S(t+dt) = S(t)*exp( (r(t)-0.5*sigma(t)**2)*dt + sigma(t)*square(dt)*Z )
	//Euler Scheme2: S(t+dt) = S(t) + S(t)*r(t)*dt + S(t)*sigma(t)*square(dt)*Z
	//Milstein Scheme1: S(t+dt) = S(t)*exp( (r(t)-0.5*sigma(t)**2)*dt + sigma(t)*square(dt)*Z )
	//Milstein Scheme2: S(t+dt) = S(t) + S(t)*r(t)*dt + S(t)*sigma(t)*square(dt)*Z + 0.5*S(t)*sigma(t)**2 * (Z**2-1)

	for (int i = 0; i < n_steps; ++i) {
		//Spot_*exp(R_.Integral(0, Expiry) + itoCorrection);
		//Spot_2 = Spot_1*exp(drift + itoCorrection + rootVariance*Variaterray[i]);
		Spot_2 = Spot_1 + Spot_1*drift + Spot_1*rootVariance*Variaterray[i] + 0.5*Spot_1*variance*(Variaterray[i]*Variaterray[i]-1);
		minSpot = min(minSpot, Spot_2);
		maxSpot = max(maxSpot, Spot_2);
		Spot_1 = Spot_2;
	}
	SpotValues = Spot_2;

	return;
}

VanillaMCEngine::VanillaMCEngine(const Wrapper<VanillaOption>& TheProduct_,
	const Parameters& R_,
	const Parameters& Vol_,
	const Wrapper<RandomBase>& TheGenerator_,
	double Spot_,
	int n_steps_):
	VanillaEngine(TheProduct_, R_),
	TheGenerator(TheGenerator_),//	,Variaterray(1)
	n_steps(n_steps_),
	spot(Spot_),
	expiry(TheProduct_->GetExpiry()),
	r(R_),
	vol(Vol_)
{

	TheGenerator->ResetDimensionality(n_steps);
	Variaterray.resize(n_steps);
}
  