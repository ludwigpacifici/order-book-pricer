#ifndef SRC_PRICER_HPP
#define SRC_PRICER_HPP

#include "PricerOutput.hpp"

namespace obp {
class Pricer {
public:
  Pricer()
      : m_isNotApplicable{true}, m_lastFinalPrice{0}, m_lastFinalQuantity{0} {}

  ~Pricer() = default;
  Pricer(Pricer &&) = delete;
  Pricer &operator=(Pricer &&) = delete;
  Pricer(const Pricer &) = delete;
  Pricer &operator=(const Pricer &) = delete;

  template <typename Book>
  std::optional<PricerOutput>
  price(const std::time_t timestamp, const Side opposite_side, const Book &book,
        const Price price_hint, Quantity target_size) {

    if (!m_isNotApplicable and
        (book.priceLevels().key_comp()(m_lastFinalPrice, price_hint) or
         m_lastFinalPrice == price_hint)) {
      return std::nullopt;
    }

    return price_impl(timestamp, opposite_side, book, target_size);
  }

  template <typename Book>
  std::optional<PricerOutput>
  price(const std::time_t timestamp, const Side opposite_side, const Book &book,
        const Price price_hint, const Quantity quantity_hint,
        Quantity target_size) {

    // Reducing at the limit but not enough to go to the next price
    // level. Hence, the final price will remain the same as the
    // previous iteration.
    if (!m_isNotApplicable and m_lastFinalPrice == price_hint and
        quantity_hint >= m_lastFinalQuantity) {
      return std::nullopt;
    }

    if (!m_isNotApplicable and
        book.priceLevels().key_comp()(m_lastFinalPrice, price_hint)) {
      return std::nullopt;
    }

    return price_impl(timestamp, opposite_side, book, target_size);
  }

private:
  bool m_isNotApplicable;
  Price m_lastFinalPrice;
  Quantity m_lastFinalQuantity;

  template <typename Book>
  std::optional<PricerOutput>
  price_impl(const std::time_t timestamp, const Side opposite_side,
             const Book &book, Quantity target_size) {
    Price price;
    Price price_level;
    Quantity quantity_level;
    for (const auto &pair : book.priceLevels()) {
      price_level = std::get<const Price>(pair);

      if (std::get<Quantity>(pair) == Quantity{0}) {
        // Skip empty level
        continue;
      }

      if (target_size <= std::get<Quantity>(pair)) {
        quantity_level = target_size;
        price += Price(price_level.value * quantity_level.value);
        target_size = Quantity(0);
        break;
      } else {
        quantity_level = std::get<Quantity>(pair);
        price += Price(price_level.value * quantity_level.value);
        target_size -= quantity_level;
      }
    }

    if (target_size == Quantity(0)) {
      m_isNotApplicable = false;
      m_lastFinalPrice = price_level;
      m_lastFinalQuantity = quantity_level;
      return std::make_optional(PricerOutput{timestamp, opposite_side, price});
    }

    if (!m_isNotApplicable) {
      m_isNotApplicable = true;
      m_lastFinalPrice = price_level;
      m_lastFinalQuantity = quantity_level;
      return std::make_optional(
          PricerOutput{timestamp, opposite_side, std::nullopt});
    }

    return std::nullopt;
  }
};
} // namespace obp

#endif
