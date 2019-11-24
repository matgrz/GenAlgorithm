#include "IMutator.h"
#include "../types/Mutations.h"

#include <set>

namespace algorithm
{
namespace mutation
{
class PointMutator : public IMutator
{
public:
    PointMutator(int mutationPercentage, types::Mutations);
    void mutatePopulation(types::Population&) override;

private:
    int getBitsetLength(const types::Population&) const;
    std::set<int> getIndexToMutate(int) const;
    void performMutation(types::Point&, int);

    const types::Mutations mutationType;
};
}
}