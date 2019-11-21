#pragma once

#include <random>
#include "../types/MainTypes.h"

namespace algorithm
{
namespace crossover
{
class ICrossover	// TODO add a class which extends ICrossover and put the methods there
{
public:
	ICrossover(int crossoverPercentage)	: crossoverPercentage { crossoverPercentage }
	{
	}
	virtual ~ICrossover() = default;
	virtual types::Population doCrossover(const types::Population& population) = 0;

protected:
	bool isCrossoverPicked()
	{
		return std::rand() % 100 < crossoverPercentage;
	}

	int crossoverPercentage;
};
}
}