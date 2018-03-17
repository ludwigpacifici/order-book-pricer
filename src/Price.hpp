#ifndef SRC_PRICE_HPP
#define SRC_PRICE_HPP

#include "Configuration.hpp"

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <ostream>

namespace obp {
struct Price {
  std::uint64_t value;

  explicit Price(const std::uint64_t a_value) : value{a_value} {}

  Price() : value{0ull} {}

  Price &operator+=(const Price &other) {
    value += other.value;
    return *this;
  }
};

inline bool operator<(const Price &lhs, const Price &rhs) {
  return lhs.value < rhs.value;
}

inline bool operator>(const Price &lhs, const Price &rhs) {
  return lhs.value > rhs.value;
}

inline std::ostream &operator<<(std::ostream &stream, const Price &data) {
  return stream << std::fixed << std::setprecision(2)
                << data.value / static_cast<double>(g_price_factor);
}

inline bool operator==(const Price &lhs, const Price &rhs) {
  return lhs.value == rhs.value;
}

inline bool operator!=(const Price &lhs, const Price &rhs) {
  return lhs.value != rhs.value;
}

inline bool operator<=(const Price &lhs, const Price &rhs) {
  return lhs < rhs or lhs == rhs;
}
} // namespace obp

#endif
