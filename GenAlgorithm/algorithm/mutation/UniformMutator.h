#include "IMutator.h"
#include "../types/Mutations.h"

#include <set>

namespace algorithm
{
namespace mutation
{
class UniformMutator : public IMutator
{
public:
    UniformMutator(int mutationPercentage, float minVal, float maxVal);
    void mutatePopulation(types::Population&) override;

private:
    void performMutation(types::Point&);
    bool shouldXIndexBeMutated();

    const float minVal;
    const float maxVal;
};
}
}
