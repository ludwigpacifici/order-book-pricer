#pragma once

#include "Order.hpp"

#include <istream>

namespace obp {

std::optional<Order>
read_one(std::istream& stream)
{
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

      char side_;
      stream >> side_;
      const auto side = side_from(side_);
      if (!side) {
        std::cerr << "Cannot read one order. Info: timestamp was: " << timestamp
                  << ", order id: " << order_id << ", side: " << side_ << '\n';
        return std::nullopt;
      }

      double price;
      stream >> price;

      std::uint64_t size;
      stream >> size;

      return std::make_optional<obp::Order>(
        OrderType::AddOrder,
        AddOrder{ timestamp, order_id, *side, Price(price, 100), { size } });
    }

    case OrderType::ReduceOrder: {
      std::string order_id;
      stream >> order_id;

      std::uint64_t size;
      stream >> size;

      return std::make_optional<obp::Order>(
        OrderType::ReduceOrder, ReduceOrder{ timestamp, order_id, { size } });
    }

    default:
      std::cerr << "Cannot read one order. Info: timestamp was: " << timestamp
                << '\n';
      return std::nullopt;
  }
}
}
