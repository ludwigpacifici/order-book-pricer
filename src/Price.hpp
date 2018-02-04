#pragma once

#include <cstdint>
#include <ostream>

namespace obp {
struct Price
{
  std::uint64_t value;
};

std::ostream&
operator<<(std::ostream& stream, const Price& data)
{
  return stream << data.value;
}
}
