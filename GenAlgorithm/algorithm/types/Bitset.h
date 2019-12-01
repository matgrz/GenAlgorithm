#pragma once

#include <vector>
#include <random>
#include <string>
#include <numeric>

namespace algorithm
{
namespace types
{
class Bitset
{
public:
    Bitset(int length);
    Bitset(std::vector<bool> bits);
    Bitset() {}

    const std::vector<bool>& getValue() const;
    std::string toString() const;
    int toDecimal() const;
    std::pair<std::vector<bool>, std::vector<bool>> splitAtIndex(int index) const;
    std::pair<std::vector<bool>, std::vector<bool>> splitAtHalf() const;
    void doCrossover(std::vector<bool> leftPart, std::vector<bool> rightPart);
    void negateBit(int index);
    void negateLeftBit();
    void negateRightBit();

    void operator=(Bitset rhs);
    bool operator==(const Bitset& rhs) const;
    Bitset operator+(const Bitset& rhs);

private:
    std::vector<bool> value{};
};
}
}
