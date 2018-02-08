#pragma once

#include <cstdint>
#include <ostream>

namespace obp {
struct Price
{
  std::uint64_t value;

  Price(const double v, const unsigned int decimal_count)
    : value(static_cast<std::uint64_t>(v * decimal_count))
  {
  }
};

std::ostream&
operator<<(std::ostream& stream, const Price& data)
{
  return stream << data.value;
}
}
