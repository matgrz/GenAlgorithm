#include "BestIndividualSelector.h"

namespace algorithm
{
namespace selection
{
BestIndividualSelector::BestIndividualSelector(const int percentage)
    : percentage{ percentage }
{
}

std::map<float, types::Point>  
BestIndividualSelector::select(const std::map<float, types::Point>& results) const
{
    std::map<float, types::Point> selectedResults = results;
    const int deletedCreaturesCount = results.size() -  static_cast<int>(percentage / 100.0 * results.size());

    for (int index = 0; index < deletedCreaturesCount; index++)
        selectedResults.erase(std::prev(selectedResults.end())->first);

    return selectedResults;
}
}
}
