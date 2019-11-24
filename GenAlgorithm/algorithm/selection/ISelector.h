#pragma once

#include <map>
#include "../types/MainTypes.h"

namespace algorithm
{
namespace selection
{
class ISelector
{
public:
    virtual ~ISelector() = default;
    virtual std::map<float, types::Point> select(const std::map<float, types::Point>&) const = 0;
};
}
}
