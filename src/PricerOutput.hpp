#ifndef SRC_PRICEROUTPUT_H
#define SRC_PRICEROUTPUT_H

#include "Price.hpp"
#include "Side.hpp"

#include <ctime>
#include <string>

namespace obp {
struct PricerOutput {
  std::time_t timestamp;
  Side action;
  std::optional<Price> total;
};

inline std::ostream &operator<<(std::ostream &stream,
                                const PricerOutput &data) {
  stream << "{"
         << R"("timestamp": )" << data.timestamp << ", "
         << R"("action": )" << data.action << ", "
         << R"("total": )";

  if (data.total) {
    stream << *data.total;
  } else {
    stream << "NA";
  }
  return stream << "}";
}
} // namespace obp

#endif
