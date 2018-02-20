#ifndef ADD_REDUCEORDER_HPP
#define ADD_REDUCEORDER_HPP

#include "Quantity.hpp"

#include <ctime>
#include <string>

namespace obp {
struct ReduceOrder {
  std::time_t timestamp;
  std::string order_id;
  Quantity size;
};

inline std::ostream &operator<<(std::ostream &stream, const ReduceOrder &data) {
  return stream << "{"
                << R"("timestamp": )" << data.timestamp << ", "
                << R"("order_id": ")" << data.order_id << R"(", )"
                << R"("size": )" << data.size << "}";
}
} // namespace obp

#endif
