#pragma once

#include "ISelector.h"

namespace algorithm
{
namespace selection
{
class TournamentSelector : public ISelector
{
public:
    TournamentSelector(const int tournamentSize);
    std::map<float, types::Point> select(const std::map<float, types::Point>&) const  override;

private:
    const int tournamentSize;
};
}
}
