#pragma once

#include <cstdint>
#include <iomanip>
#include <ostream>

namespace obp {
struct Price {
  float value;

  explicit Price(const float a_value) : value{a_value} {}

  Price() : value{0.0f} {}

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

  return stream << std::fixed << std::setprecision(2) << data.value;
}
} // namespace obp
