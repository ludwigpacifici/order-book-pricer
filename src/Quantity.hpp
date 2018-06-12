#ifndef SRC_QUANTITY_HPP
#define SRC_QUANTITY_HPP

#include <cstdint>
#include <ostream>

namespace obp {
struct Quantity {
  std::uint64_t value;

  Quantity() : value{0} {}

  explicit Quantity(const std::uint64_t a_value) : value{a_value} {}

  ~Quantity() = default;
  Quantity(const Quantity &) = default;
  Quantity(Quantity &&) = default;
  Quantity &operator=(const Quantity &) = default;
  Quantity &operator=(Quantity &&) = default;

  Quantity &operator-=(const Quantity &other) {
    value -= other.value;
    return *this;
  }

  Quantity &operator+=(const Quantity &other) {
    value += other.value;
    return *this;
  }
};

inline std::ostream &operator<<(std::ostream &stream, const Quantity &data) {
  return stream << data.value;
}

inline bool operator<(const Quantity &lhs, const Quantity &rhs) {
  return lhs.value < rhs.value;
}

inline bool operator>(const Quantity &lhs, const Quantity &rhs) {
  return lhs.value > rhs.value;
}

inline bool operator==(const Quantity &lhs, const Quantity &rhs) {
  return lhs.value == rhs.value;
}

inline bool operator!=(const Quantity &lhs, const Quantity &rhs) {
  return lhs.value != rhs.value;
}

inline bool operator>=(const Quantity &lhs, const Quantity &rhs) {
  return lhs > rhs or lhs == rhs;
}

inline bool operator<=(const Quantity &lhs, const Quantity &rhs) {
  return lhs < rhs or lhs == rhs;
}
} // namespace obp

#endif
