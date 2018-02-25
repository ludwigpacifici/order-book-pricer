#ifndef SRC_PRICER_HPP
#define SRC_PRICER_HPP

#include "PricerOutput.hpp"

namespace obp {
class Pricer {
public:
  Pricer() : m_startEmitOutput{false} {}

  template <typename Book>
  std::optional<PricerOutput> price(const std::time_t timestamp,
                                    const Side opposite_side, const Book &book,
                                    Quantity target_size) {
    Price price;
    for (const auto &pair : book.priceLevels()) {
      if (target_size < std::get<Quantity>(pair)) {
        price += Price((std::get<const Price>(pair).value / 100.0) *
                       target_size.value);
        target_size = Quantity{};
        break;
      } else {
        price += Price((std::get<const Price>(pair).value / 100.0) *
                       std::get<Quantity>(pair).value);
        target_size -= std::get<Quantity>(pair);
      }
    }

    if (target_size == Quantity{}) {
      m_startEmitOutput = true;
      return std::make_optional(PricerOutput{timestamp, opposite_side, price});
    }

    if (m_startEmitOutput) {
      return std::make_optional(
          PricerOutput{timestamp, opposite_side, std::nullopt});
    }

    return std::nullopt;
  }

private:
  bool m_startEmitOutput;
};
} // namespace obp

#endif
