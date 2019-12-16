#pragma once

#include <random>
#include <optional>
#include "MainTypes.h"

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
    using Children = std::optional<std::pair<types::Point, types::Point>>;

    CrossoverProvider(int);
    types::Population doCrossover(const types::Population& population) override;

protected:
    virtual Children crossoverTwoCreatures(const types::Point&, const types::Point&) = 0;
    int getIndexOfRandomCreatureWorseThanCurrent(int, int);
    bool isCrossoverPicked();
    float getValueFromZeroToOne() const;

    int crossoverPercentage;
};
}
}
