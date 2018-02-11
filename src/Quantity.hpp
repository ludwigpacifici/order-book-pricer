#pragma once

#include <cstdint>
#include <ostream>

namespace obp {
struct Quantity
{
  std::uint64_t value;

  Quantity& operator-=(const Quantity& rhs)
  {
    value -= rhs.value;
    return *this;
  }
};

std::ostream&
operator<<(std::ostream& stream, const Quantity& data)
{
  return stream << data.value;
}

bool
operator<(const Quantity& lhs, const Quantity& rhs)
{
  return lhs.value < rhs.value;
}

bool
operator>(const Quantity& lhs, const Quantity& rhs)
{
  return lhs.value > rhs.value;
}
}
