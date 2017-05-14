#include "wrapper.h"
#include "Parameters.h"
#include "Vanilla3.h"
#include "MCStatistics.h"
#include <vector>
#include "CashFlow.h"
#include "Arrays.h"

class DerivativeEngine
{
public:

	DerivativeEngine(const Wrapper<VanillaOption>& TheProduct_,
		const Parameters& r_);
	virtual ~DerivativeEngine(void) {}

public:
	virtual void DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths)=0;
	virtual void GetOnePath(double& SpotValues) = 0; // Use the gaussian number to simulate a spot value
	virtual double DoOnePath(const double& SpotValues) const =0; // calculating thisPayoff by thisSpot and discount

private:
};