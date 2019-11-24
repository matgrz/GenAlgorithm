#include "RouletteSelector.h"

#include <algorithm>
#include <random>
#include <iostream>

namespace algorithm
{
namespace selection
{
RouletteSelector::RouletteSelector(int killCount) : killCount{killCount}
{
}
std::map<float, types::Point> RouletteSelector::select(const std::map<float, types::Point>& results) const
{
    auto distributions = getDistributions(results);	
    auto resultsToRemove = getResultsToBeRemoved(results , distributions);
    return removeSelectedResults(results, resultsToRemove);
}

std::vector<float> RouletteSelector::getDistributions(const std::map<float, types::Point>& resultsBeforeRoulette) const
{
    float sum = calculateResultSum(resultsBeforeRoulette);
    std::vector<float> weights = calculateWeights(resultsBeforeRoulette, sum);

    std::vector<float> distributions{ weights.front() };
    for (int index = 1; index < resultsBeforeRoulette.size() - 1; index++)
    {
    distributions.push_back(distributions[index - 1] + weights[index]);
    }
    distributions.push_back(1.0);

    return distributions;
}

float RouletteSelector::calculateResultSum(const std::map<float, types::Point>& resultsBeforeRoulette) const
{
    return std::accumulate(resultsBeforeRoulette.begin(),
                           resultsBeforeRoulette.end(),
                           0,
                           [](int value, const auto& creature) {
                                return value + creature.first;
                           });
}

std::vector<float> RouletteSelector::calculateWeights(
    const std::map<float, types::Point>& resultsBeforeRoulette,
    const float sum) const
{
    std::vector<float> weights{};
    for (const auto& creature : resultsBeforeRoulette)
        weights.push_back(creature.first / sum);

    return weights;
}

std::set<int> RouletteSelector::getIndexesToKill(const std::vector<float>& distributions) const
{
    std::set<int> indexesToKill{};

    for (int iteration = 0; iteration < killCount; iteration++)
    {
        const float randomValue = getRandomFloatZeroToOneInclusive();
        int index = 0;

        for (const float& distribution : distributions)
        {
            if (randomValue < distribution)
            {
                indexesToKill.insert(index);
                break;
            }
            ++index;
        }
    }
    return indexesToKill;
}
float RouletteSelector::getRandomFloatZeroToOneInclusive() const
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);;
}

std::map<float, types::Point> RouletteSelector::getResultsToBeRemoved(
    const std::map<float, types::Point>& results, 
    const std::vector<float>& distributions) const
{
    auto indexesToKill = getIndexesToKill(distributions);
    std::map<float, types::Point> resultsToRemove{};

    for (const auto& indexToKill : indexesToKill)
    {
        auto resultsIter = results.begin();
        for (int index = 0; index < indexToKill; index++)
            ++resultsIter;

        resultsToRemove.insert(*resultsIter);
    }

    return resultsToRemove;
}

std::map<float, types::Point> RouletteSelector::removeSelectedResults(
    const std::map<float, types::Point>& resultsBeforeRoulette,
    const std::map<float, types::Point>& resultsToRemove) const
{
    auto resultsAfterSelection = resultsBeforeRoulette;
    for (const auto& resultToRemove : resultsToRemove)
        resultsAfterSelection.erase(resultToRemove.first);

    return resultsAfterSelection;
}
}
}
