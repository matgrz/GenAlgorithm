#pragma once

#include "IMutator.h"

namespace algorithm
{
namespace mutation
{
class IndexChangeMutator : public IMutator
{
public:
    IndexChangeMutator(int mutationPercentage);
    void mutatePopulation(types::Population&) override;

private:
    void mutateCreature(types::Point&);
};
}
}
