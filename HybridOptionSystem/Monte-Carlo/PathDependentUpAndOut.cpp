#include "PathDependentUpAndOut.h"

PathDependentUpAndOut::PathDependentUpAndOut(const MJArray&
                                             LookAtTimes_,
                                             double DeliveryTime_,
                                             const PayOffBridge&ThePayOff_,
                                             double Barrier_)
:
PathDependent(LookAtTimes_),
DeliveryTime(DeliveryTime_),
ThePayOff(ThePayOff_),
NumberOfTimes(LookAtTimes_.size()),
Barrier(Barrier_)
{
}

unsigned long PathDependentUpAndOut::MaxNumberOfCashFlows() const
{
    return 1UL;
}
MJArray PathDependentUpAndOut::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}
unsigned long PathDependentUpAndOut::CashFlows(const MJArray&
                                            SpotValues,
                                            std::vector<CashFlow>& GeneratedFlows) const
{
    //double sum = SpotValues.sum();
    double max = SpotValues.max();
    double final = SpotValues[NumberOfTimes-1];
    double knock_out_price;
    if(max>Barrier){
        knock_out_price=0;
    }else{
        knock_out_price=final;
    }
    //double mean = sum/NumberOfTimes;
    GeneratedFlows[0].TimeIndex = 0UL;
//    GeneratedFlows[0].Amount = ThePayOff(mean);
    GeneratedFlows[0].Amount = ThePayOff(knock_out_price);
    return 1UL;
}
PathDependent* PathDependentUpAndOut::clone() const
{
    return new PathDependentUpAndOut(*this);
}