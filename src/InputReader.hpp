#ifndef SRC_INPUTREADER_HPP
#define SRC_INPUTREADER_HPP

#include "Order.hpp"

#include <istream>

namespace obp {

namespace internal {
inline std::string remove_decimal_separator(std::string price) {
  price[price.size() - 3] = price[price.size() - 2];
  price[price.size() - 2] = price[price.size() - 1];
  price.pop_back();

  return price;
}
} // namespace internal

inline std::optional<Order> read_one(std::istream &stream) {
  std::time_t timestamp;
  stream >> timestamp;

  char order_type_;
  stream >> order_type_;

  const auto order_type = order_type_from(order_type_);
  if (!order_type) {
    std::cerr << "Cannot read one order. Info: timestamp was: " << timestamp
              << '\n';
    return std::nullopt;
  }

  switch (*order_type) {
  case OrderType::AddOrder: {
    std::string order_id;
    stream >> order_id;
    if (order_id.empty()) {
      std::cerr << "No order id provided\n";
      return std::nullopt;
    }

    char side_;
    stream >> side_;
    const auto side = side_from(side_);
    if (!side) {
      std::cerr << "Cannot read one order. Info: timestamp was: " << timestamp
                << ", order id: " << order_id << ", side: " << side_ << '\n';
      return std::nullopt;
    }

    std::string buffer;
    stream >> buffer;
    const std::uint64_t price =
        std::stoull(internal::remove_decimal_separator(buffer));

    std::uint64_t size;
    stream >> size;

    return std::make_optional<obp::Order>(
        AddOrder{timestamp, order_id, *side, Price(price), Quantity{size}});
  }

  case OrderType::ReduceOrder: {
    std::string order_id;
    stream >> order_id;

    std::uint64_t size;
    stream >> size;

    return std::make_optional<obp::Order>(
        ReduceOrder{timestamp, order_id, Quantity{size}});
  }

  default:
    std::cerr << "Cannot read one order. Info: timestamp was: " << timestamp
              << '\n';
    return std::nullopt;
  }
}
} // namespace obp

#endif
