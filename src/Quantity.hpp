#pragma once

#include <cstdint>
#include <ostream>

namespace obp {
struct Quantity
{
  std::uint64_t value;
};

std::ostream&
operator<<(std::ostream& stream, const Quantity& data)
{
  return stream << data.value;
}
}
