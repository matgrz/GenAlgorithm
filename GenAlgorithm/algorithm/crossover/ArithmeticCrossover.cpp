#include "ArithmeticCrossover.h"

namespace algorithm
{
namespace crossover
{
ArithmeticCrossover::ArithmeticCrossover(int crossoverPercentage)
    : CrossoverProvider{ crossoverPercentage }
{
}

CrossoverProvider::Children ArithmeticCrossover::crossoverTwoCreatures(const types::Point& firstParent, const types::Point& secondParent)
{
    const auto k = getValueFromZeroToOne();
    types::Point firstChild;
    types::Point secondChild;
    
    firstChild.first = k * firstParent.first + (1.0 - k) * secondParent.first;
    firstChild.second = k * firstParent.second + (1.0 - k) * secondParent.second;

    secondChild.first = (1.0 - k) * firstParent.first + k * firstParent.first;
    secondChild.second = (1.0 - k) * firstParent.second + k * firstParent.second;
    return { { firstChild, secondChild } };
}
}
}
