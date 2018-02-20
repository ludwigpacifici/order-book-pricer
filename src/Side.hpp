#ifndef SRC_SIDE_HPP
#define SRC_SIDE_HPP

#include <iostream>
#include <optional>

namespace obp {
enum class Side { Bid, Ask };

inline std::optional<Side> side_from(char side) {
  switch (side) {
  case 'B':
  case 'b':
    return Side::Bid;
  case 'S':
  case 's':
    return Side::Ask;
  default:
    std::cerr << "Invalid side: " << side
              << ", ASCII code: " << static_cast<int>(side) << '\n';
    return std::nullopt;
  }
}

inline std::ostream &operator<<(std::ostream &stream, const Side &data) {
  switch (data) {
  case Side::Bid:
    return stream << "Bid";
  case Side::Ask:
    return stream << "Ask";
  default:
    return stream << "Unknown Side";
  }
}
} // namespace obp

#endif
