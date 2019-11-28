#pragma once

#include "Bitset.h"

#include <set>
#include <map>

namespace algorithm
{
namespace types
{
using xValues = types::Bitset;
using yValues = types::Bitset;
using Point = std::pair<xValues, yValues>;
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
