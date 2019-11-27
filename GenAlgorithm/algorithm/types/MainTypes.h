#pragma once

#include "Bitset.h"

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
}
}
