#ifndef PATH_DEPENDENT_ASIAN_H
#define PATH_DEPENDENT_ASIAN_H
#include "PathDependent.h"
#include "PayOffBridge.h"
class PathDependentUpAndOut : public PathDependent
{
public:
    PathDependentUpAndOut(const MJArray& LookAtTimes_,
                          double DeliveryTime_,
                          const PayOffBridge& ThePayOff_,
                          double Barrier_);
    
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentUpAndOut(){}
    virtual PathDependent* clone() const;
private:
    double DeliveryTime;
    double Barrier;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};
#endif