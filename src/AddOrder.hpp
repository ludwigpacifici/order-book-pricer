#ifndef SRC_ADDORDER_HPP
#define SRC_ADDORDER_HPP

#include "Price.hpp"
#include "Quantity.hpp"
#include "Side.hpp"

#include <ctime>
#include <string>

namespace obp {
struct AddOrder {
  std::time_t timestamp;
  std::string order_id;
  Side side;
  Price price;
  Quantity size;
};

inline std::ostream &operator<<(std::ostream &stream, const AddOrder &data) {
  return stream << "{"
                << R"("timestamp": )" << data.timestamp << ", "
                << R"("order_id": ")" << data.order_id << R"(", )"
                << R"("side": ")" << data.side << R"(", )"
                << R"("price": )" << data.price << ", "
                << R"("size": )" << data.size << "}";
}
} // namespace obp
#endif
