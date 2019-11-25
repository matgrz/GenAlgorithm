#pragma once

#include <vector>
#include <random>
#include <string>
#include <numeric>

namespace algorithm
{
namespace types
{
    // TODO make a src file 
    class Bitset
    {
    public:
    Bitset(int length)
    {
        for (int index = 0; index < length; index++)
        {
            value.push_back(std::rand() % 2 == 1);
        }
    }

    Bitset(std::vector<bool> bits)
    {
        value = std::move(bits);
    }

    Bitset() {}

    const std::vector<bool>& getValue() const
    {
        return value;
    }

    std::string toString() const
    {
        std::string valueString{""};
        for (const auto& element : value)
            valueString.append(std::to_string(element));
        return valueString;
    }

    int toDecimal() const
    {
        return  std::accumulate(value.begin(), value.end(), 0, [](int x, int y) 
            { 
                return (x << 1) + y; 
            });
    }

    std::pair<std::vector<bool>, std::vector<bool>> splitAtIndex(int index) const
    {
        return { {value.begin(), value.begin() + index}, {value.begin() + index, value.end()} };
    }

    std::pair<std::vector<bool>, std::vector<bool>> splitAtHalf() const
    {
        return splitAtIndex(value.size() / 2);
    }

    void operator=(Bitset rhs)
    {
        value = rhs.getValue();
    }

    bool operator==(const Bitset& rhs) const
    {
        return this->toString() == rhs.toString();
    }

    Bitset operator+(const Bitset& rhs)
    {
        auto lhsValue = this->value;
        auto rhsValue = rhs.getValue();
        lhsValue.insert(lhsValue.end(), rhsValue.begin(), rhsValue.end());
        return Bitset{ lhsValue };
    }

    void doCrossover(std::vector<bool> leftPart, std::vector<bool> rightPart)
    {
        value.insert(value.begin(), leftPart.begin(), leftPart.end());
        value.insert(value.begin() + leftPart.size(), rightPart.begin(), rightPart.end());
    }

    void negateBit(int index)
    {
        value[index] = !value[index];
    }

    void negateLeftBit()
    {
        negateBit(0);
    }

    void negateRightBit()
    {
        negateBit(value.size() - 1);
    }

private:
    std::vector<bool> value{};
};
}
}
