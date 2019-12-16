#pragma once
#include "SelectionMethods.h"
#include "Crossovers.h"
#include "Mutations.h"

namespace algorithm
{
namespace types
{
struct InputData
{
    int populationSize;
    int generationCount;
    int strategyPercent;
    SelectionMethods selectionMethod;
    int selectionParameter;
    Crossovers crossoverMethod;
    int crossoverProbability;
    Mutations mutationMethod;
    int mutationProbability;
    float centerX;
    float centerY;
    float radius;
};
}
}
