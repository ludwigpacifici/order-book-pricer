#pragma once

#include "AddOrder.hpp"
#include "PricerOutput.hpp"

#include <unordered_map>

namespace obp {

class OrderFollower {
public:
  struct AddOrderAnonymous {
    std::time_t timestamp;
    Side side;
    Price price;
    Quantity size;
  };

  bool add(const AddOrder &order) {
    const auto pair = m_orders.emplace(std::make_pair(
        order.order_id, AddOrderAnonymous{order.timestamp, order.side,
                                          order.price, order.size}));

    return std::get<1>(pair);
  }

  std::optional<AddOrderAnonymous> reduce(const ReduceOrder &order) {
    if (auto it = m_orders.find(order.order_id); it == std::cend(m_orders)) {
      std::cerr << "Reduce order not found: " << order << '\n';
      return std::nullopt;
    } else if (it->second.size > order.size) {
      it->second.size -= order.size;
      return it->second;
    } else {
      const auto ret = AddOrderAnonymous{it->second.timestamp, it->second.side,
                                         it->second.price, Quantity{0}};
      m_orders.erase(it);
      return ret;
    }
  }

private:
  std::unordered_map<std::string, AddOrderAnonymous> m_orders;
};
} // namespace obp
