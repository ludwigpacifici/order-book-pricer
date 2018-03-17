#ifndef SRC_ORDER_HPP
#define SRC_ORDER_HPP

#include "AddOrder.hpp"
#include "Overloaded.hpp"
#include "ReduceOrder.hpp"

#include <iostream>
#include <variant>

namespace obp {
enum class OrderType { AddOrder, ReduceOrder };

inline std::optional<OrderType> order_type_from(const char type) {
  switch (type) {
  case 'A':
  case 'a':
    return OrderType::AddOrder;

  case 'R':
  case 'r':
    return OrderType::ReduceOrder;

  default:
    std::cerr << "Invalid order type: " << type
              << ", ASCII code: " << static_cast<int>(type) << '\n';
    return std::nullopt;
  }
}

inline std::string to_string(const OrderType data) {
  switch (data) {
  case OrderType::AddOrder:
    return "AddOrder";

  case OrderType::ReduceOrder:
    return "ReduceOrder";

  default:
    return "Unknown OrderType";
  }
}

using Order = std::variant<AddOrder, ReduceOrder>;

inline std::ostream &operator<<(std::ostream &stream, const Order &data) {
  return std::visit(
      help::overloaded{
          [&stream](const AddOrder &data) -> std::ostream & {
            if constexpr (g_format == OutputFormat::Compact) {
              stream << data;
            } else {
              stream << R"({")" << to_string(OrderType::AddOrder) << R"(": )"
                     << data << "}";
            }
            return stream;
          },
          [&stream](const ReduceOrder &data) -> std::ostream & {
            if constexpr (g_format == OutputFormat::Compact) {
              stream << data;
            } else {
              stream << R"({")" << to_string(OrderType::ReduceOrder) << R"(": )"
                     << data << "}";
            }
            return stream;
          },
      },
      data);
}
} // namespace obp

#endif
