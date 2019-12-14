#pragma once

#include <set>
#include <map>
#include <vector>

namespace algorithm
{
namespace types
{
using Point = std::pair<float, float>;
using Population = std::vector<Point>;

struct ResultValues
{
    float x;
    float y;
    float z;

    bool operator<(const ResultValues& lhs) const 
    { 
        return z < lhs.z;
    }
};

using SortedResults = std::set<ResultValues>;
using ResultsPerIteration = std::map<int, SortedResults>;
}
}
