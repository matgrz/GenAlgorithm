#include "TournamentSelector.h"

namespace algorithm
{
namespace selection
{
TournamentSelector::TournamentSelector(const int tournamentSize)
    : tournamentSize{ tournamentSize }
{
}

std::map<float, types::Point>  TournamentSelector::select(const std::map<float, types::Point>& results) const
{
    std::map<float, types::Point> tournament = results;
    std::map<float, types::Point> winners{};

    while (tournament.size() >= tournamentSize)
        winners.insert(createArenaAndGetWinner(tournament));

    getWinnerIfThereWasIncompleteArena(tournament, winners);
    return winners;
}

std::pair<float, types::Point>
TournamentSelector::createArenaAndGetWinner(std::map<float, types::Point>& tournament) const
{
    std::map<float, types::Point> arena{};
    for (int index = 0; index < tournamentSize; index++)
    {
        const int indexToPickParticipant = getRandomIndex(tournament.size());
        arena.insert(moveParticipantToArena(tournament, indexToPickParticipant));
    }
    return *arena.begin();
}

int TournamentSelector::getRandomIndex(int currentTournamentSize) const
{
    return std::rand() % currentTournamentSize;
}

std::pair<float, types::Point>
TournamentSelector::moveParticipantToArena(std::map<float, types::Point>& tournament, int randomIndex) const
{
    auto iter = tournament.begin();
    for (int index = 0; index < randomIndex; index++)
        ++iter;

    auto participantCopy = *iter;
    tournament.erase(participantCopy.first);
    return participantCopy;
}

void TournamentSelector::getWinnerIfThereWasIncompleteArena(const std::map<float, types::Point>& tournament, 
                                                            std::map<float, types::Point>& winners) const
{
    if (tournament.size())
        winners.insert(*tournament.begin());
}
}
}
