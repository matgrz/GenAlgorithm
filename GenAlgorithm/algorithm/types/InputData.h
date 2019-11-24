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
    int accuracy;
    int populationSize;
    int generationCount;
    int inversionProbability;
    int strategyPercent;
    SelectionMethods selectionMethod;
    int selectionParameter;
    Crossovers crossoverMethod;
    int crossoverProbability;
    Mutations mutationMethod;
    int mutationProbability;
};
}
}
