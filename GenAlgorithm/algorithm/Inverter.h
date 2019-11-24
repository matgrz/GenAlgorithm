#pragma once

#include "types/MainTypes.h"

namespace algorithm
{
class Inverter
{
public:
    Inverter(int inversionProbability);
    void performInversion(types::Population&);

private:
    bool shouldPerformInversion() const;
    void invertPartOfBitset(types::Point&);
    bool shouldInvertX() const;
    int getLowerIndex(const types::Bitset&) const;
    int getUpperIndex(const types::Bitset&) const;
    void doInvertion(types::Bitset&);

    const int inversionProbability;
};
}
