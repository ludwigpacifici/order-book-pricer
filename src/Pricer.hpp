#ifndef SRC_PRICER_HPP
#define SRC_PRICER_HPP

#include "PricerOutput.hpp"

namespace obp {
class Pricer {
public:
  Pricer() : m_isNotApplicable{true} {}

  template <typename Book>
  std::optional<PricerOutput> price(const std::time_t timestamp,
                                    const Side opposite_side, const Book &book,
                                    Quantity target_size) {
    Price price;
    for (const auto &pair : book.priceLevels()) {
      if (target_size < std::get<Quantity>(pair)) {
        price += Price(std::get<const Price>(pair).value * target_size.value);
        target_size = Quantity(0);
        break;
      } else {
        price += Price(std::get<const Price>(pair).value *
                       std::get<Quantity>(pair).value);
        target_size -= std::get<Quantity>(pair);
      }
    }

    if (target_size == Quantity(0)) {
      m_isNotApplicable = false;
      return std::make_optional(PricerOutput{timestamp, opposite_side, price});
    }

    if (m_isNotApplicable == false) {
      m_isNotApplicable = true;
      return std::make_optional(
          PricerOutput{timestamp, opposite_side, std::nullopt});
    }

    return std::nullopt;
  }

private:
  bool m_isNotApplicable;
};
} // namespace obp

#endif
