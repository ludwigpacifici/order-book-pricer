#pragma once

#include <cstdint>
#include <ostream>

namespace obp {
struct Price {
  std::uint64_t value;

  Price(const double v, const unsigned int decimal_count)
      : value(static_cast<std::uint64_t>(v * decimal_count)) {}

  explicit Price(const std::uint64_t a_value) : value{a_value} {}
};

inline bool operator<(const Price &lhs, const Price &rhs) {
  return lhs.value < rhs.value;
}

inline bool operator>(const Price &lhs, const Price &rhs) {
  return lhs.value > rhs.value;
}

inline std::ostream &operator<<(std::ostream &stream, const Price &data) {
  return stream << data.value;
}
} // namespace obp
