#pragma once

#include "ISelector.h"

namespace algorithm
{
namespace selection
{
class BestIndividualSelector : public ISelector
{
public:
    BestIndividualSelector(const int percentage);
    std::map<float, types::Point> select(const std::map<float, types::Point>&) const  override;

private:
    const int percentage;
};
}
}
