#pragma once

#include "ISelector.h"
#include <set>

namespace algorithm
{
namespace selection
{
class RouletteSelector : public ISelector
{
public:
	RouletteSelector(int killCount);
	std::map<float, types::Point> select(const std::map<float, types::Point>&) const override;

private:
	std::vector<float> getDistributions(const std::map<float, types::Point>&) const;
	float calculateResultSum(const std::map<float, types::Point>&) const;
	std::vector<float> calculateWeights(const std::map<float, types::Point>&, const float) const;
	std::set<int> getIndexesToKill(const std::vector<float>& distributions) const;
	float getRandomFloatZeroToOneInclusive() const;
	std::map<float, types::Point> getResultsToBeRemoved(const std::map<float, types::Point>&, 
														const std::vector<float>&) const;
	std::map<float, types::Point> removeSelectedResults(const std::map<float, types::Point>&, 
														const std::map<float, types::Point>&) const;

	const int killCount;
};
}
}