#pragma once

#include "Price.hpp"
#include "Quantity.hpp"

#include <map>

namespace obp {
template<typename CompareFn>
class AnonymousBook
{
private:
  using PriceQuantity = std::map<Price, Quantity, CompareFn>;

public:
  const PriceQuantity& priceLevels() const { return m_priceLevels; }

  Quantity add(const Price& price, const Quantity& size)
  {
    auto& current_size = m_priceLevels[price];
    current_size += size;
    return current_size;
  }

  Quantity reduce(const Price& price, const Quantity& size)
  {
    auto& current_size = m_priceLevels[price];
    if (size < current_size) {
      current_size -= size;
    } else {
      current_size = Quantity{ 0 };
    }
    return current_size;
  }

private:
  PriceQuantity m_priceLevels;
};

using AnonymousBookBuy = AnonymousBook<std::greater<Price>>;
using AnonymousBookSell = AnonymousBook<std::less<Price>>;
}
