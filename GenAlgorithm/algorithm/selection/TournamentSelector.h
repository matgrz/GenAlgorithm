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
    std::pair<float, types::Point> createArenaAndGetWinner(std::map<float, types::Point>&) const;
    int getRandomIndex(int) const;
    std::pair<float, types::Point> moveParticipantToArena(std::map<float, types::Point>&, int) const;
    void getWinnerIfThereWasIncompleteArena(const std::map<float, types::Point>&,
                                            std::map<float, types::Point>&) const;

    const int tournamentSize;
};
}
}
