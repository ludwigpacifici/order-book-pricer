#pragma once

#include "AddOrder.hpp"
#include "ReduceOrder.hpp"

#include <iostream>

namespace obp {
enum class OrderType
{
  AddOrder,
  ReduceOrder
};

std::string
to_string(const OrderType data)
{
  switch (data) {
    case OrderType::AddOrder:
      return "AddOrder";

    case OrderType::ReduceOrder:
      return "ReduceOrder";

    default:
      return "Unknown OrderType";
  }
}

struct Order
{
  union Orders
  {
    AddOrder add;
    ReduceOrder reduce;

    ~Orders() {}
    Orders(const AddOrder& data)
      : add(data)
    {
    }
    Orders(AddOrder&& data)
      : add(std::move(data))
    {
    }
    Orders(const ReduceOrder& data)
      : reduce(data)
    {
    }
    Orders(ReduceOrder&& data)
      : reduce(std::move(data))
    {
    }
  };

  OrderType type;
  Orders data;

  template<typename T>
  Order(const OrderType t, T&& o)
    : type(t)
    , data(std::forward<T>(o))
  {
  }
};

std::ostream&
operator<<(std::ostream& stream, const Order& data)
{
  switch (data.type) {
    case OrderType::AddOrder:
      return stream << to_string(data.type) << ": " << data.data.add;

    case OrderType::ReduceOrder:
      return stream << to_string(data.type) << ": " << data.data.reduce;

    default:
      return stream << to_string(data.type);
  }
}
}
