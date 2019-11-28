#pragma once

#include <random>
#include "MainTypes.h"

namespace algorithm
{
namespace mutation
{
class IMutator	// TODO create a class which extends IMutator and move the fuctionality there
{
public:
    IMutator(int mutationPercentage) : mutationPercentage{ mutationPercentage }
    {
    }

    virtual ~IMutator() = default;
    virtual void mutatePopulation(types::Population&) = 0;

protected:
    bool shouldMutationOccur()
    {
        return std::rand() % 100 < mutationPercentage;
    }

    int mutationPercentage;
};
}
}
