#include "Bitset.h"

namespace algorithm
{
namespace types
{
Bitset::Bitset(int length)
{
    for (int index = 0; index < length; index++)
        value.push_back(std::rand() % 2 == 1);
}

Bitset::Bitset(std::vector<bool> bits)
{
    value = std::move(bits);
}

const std::vector<bool>& Bitset::getValue() const
{
    return value;
}

std::string Bitset::toString() const
{
    std::string valueString{ "" };
    for (const auto& element : value)
        valueString.append(std::to_string(element));
    return valueString;
}

int Bitset::toDecimal() const
{
    return  std::accumulate(value.begin(), value.end(), 0, [](int x, int y)
    {
        return (x << 1) + y;
    });
}

std::pair<std::vector<bool>, std::vector<bool>> Bitset::splitAtIndex(int index) const
{
    return { {value.begin(), value.begin() + index}, {value.begin() + index, value.end()} };
}

std::pair<std::vector<bool>, std::vector<bool>> Bitset::splitAtHalf() const
{
    return splitAtIndex(value.size() / 2);
}

void Bitset::doCrossover(std::vector<bool> leftPart, std::vector<bool> rightPart)
{
    value.insert(value.begin(), leftPart.begin(), leftPart.end());
    value.insert(value.begin() + leftPart.size(), rightPart.begin(), rightPart.end());
}

void Bitset::negateBit(int index)
{
    value[index] = !value[index];
}

void Bitset::negateLeftBit()
{
    negateBit(0);
}

void Bitset::negateRightBit()
{
    negateBit(value.size() - 1);
}

void Bitset::operator=(Bitset rhs)
{
    value = rhs.getValue();
}

bool Bitset::operator==(const Bitset& rhs) const
{
    return this->toString() == rhs.toString();
}

Bitset Bitset::operator+(const Bitset& rhs)
{
    auto lhsValue = this->value;
    auto rhsValue = rhs.getValue();
    lhsValue.insert(lhsValue.end(), rhsValue.begin(), rhsValue.end());
    return Bitset{ lhsValue };
}
}
}