#pragma once

#include <random>
#include "../types/MainTypes.h"

namespace algorithm
{
namespace crossover
{
class ICrossover
{
public:
    virtual ~ICrossover() = default;
    virtual types::Population doCrossover(const types::Population&) = 0;
};

class CrossoverProvider : public ICrossover
{
public:
    CrossoverProvider(int);
    types::Population doCrossover(const types::Population& population) override;

protected:
    virtual std::pair<types::Point, types::Point> 
        crossoverTwoCreatures(const types::Point&, const types::Point&) = 0;
    int getIndexOfRandomCreatureWorseThanCurrent(int, int);
    bool isCrossoverPicked();

    int crossoverPercentage;
};
}
}
