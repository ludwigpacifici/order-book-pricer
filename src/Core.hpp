#ifndef SRC_CORE_HPP
#define SRC_CORE_HPP

#include "AnonymousBook.hpp"
#include "InputReader.hpp"
#include "OrderFollower.hpp"
#include "Pricer.hpp"

namespace obp {
namespace internal {
template <typename CallBackFn> void loop(CallBackFn &&call_back) {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line, std::ios_base::in);
    const auto order = obp::read_one(iss);

    if (order) {
      call_back(*order);
    } else {
      std::cerr << "Cannot read one order\n";
    }
  }
}
} // namespace internal

inline void loop() {
  auto no_process_orders = [](const Order &order) {
    std::cout << order << '\n';
  };

  internal::loop(no_process_orders);
}

inline void run() { loop(); }

template <typename AnonymousBook, typename Pricer>
void processOrderAddSide(AnonymousBook &book, Pricer &pricer,
                         const obp::AddOrder &add_order,
                         const Side opposite_side,
                         const obp::Quantity target_size) {
  book.add(add_order.price, add_order.size);

#ifdef DEBUG
  std::cout << "order: " << add_order << '\n';
  std::cout << "Book: " << book << '\n';
#endif

  if (const auto output = pricer.price(add_order.timestamp, opposite_side, book,
                                       add_order.price, target_size);
      output) {
    std::cout << *output << '\n';
  }
}

template <typename AnonymousBook, typename Pricer>
void processOrderReduceSide(
    AnonymousBook &book, Pricer &pricer, const ReduceOrder &reduce_order,
    const std::optional<OrderFollower::AddOrderAnonymous> &anonymous_order,
    const Side opposite_side, const Quantity target_size) {

  const auto remaining_quantity =
      book.reduce(anonymous_order->price, reduce_order.size);

#ifdef DEBUG
  std::cout << "order: " << reduce_order << '\n';
  std::cout << "Book: " << book << '\n';
#endif

  if (const auto output =
          pricer.price(reduce_order.timestamp, opposite_side, book,
                       anonymous_order->price, remaining_quantity, target_size);
      output) {
    std::cout << *output << '\n';
  }
}

inline void run(const obp::Quantity target_size) {
  obp::OrderFollower follower;
  obp::AnonymousBookBuy bookBuy;
  obp::AnonymousBookSell bookSell;
  obp::Pricer pricerBuy;
  obp::Pricer pricerSell;

  auto processOrderAdd = [&follower, &bookBuy, &bookSell, &pricerBuy,
                          &pricerSell,
                          target_size](const obp::AddOrder &add_order) {
    follower.add(add_order);

    switch (add_order.side) {
    case obp::Side::Bid:
      processOrderAddSide(bookBuy, pricerBuy, add_order, obp::Side::Ask,
                          target_size);
      break;

    case obp::Side::Ask:
      processOrderAddSide(bookSell, pricerSell, add_order, obp::Side::Bid,
                          target_size);
      break;

    default:
      std::cerr << "Unknown order add side: " << add_order.side << '\n';
      break;
    }
  };

  auto processOrderReduce =
      [&follower, &bookBuy, &bookSell, &pricerBuy, &pricerSell,
       target_size](const obp::ReduceOrder &reduce_order) {
        const auto anonymous_order = follower.reduce(reduce_order);

        switch (anonymous_order->side) {
        case obp::Side::Bid:
          processOrderReduceSide(bookBuy, pricerBuy, reduce_order,
                                 anonymous_order, obp::Side::Ask, target_size);
          break;

        case obp::Side::Ask:
          processOrderReduceSide(bookSell, pricerSell, reduce_order,
                                 anonymous_order, obp::Side::Bid, target_size);
          break;

        default:
          std::cerr << "Not there.\n";
          break;
        }
      };

  auto process_orders = [processOrderAdd,
                         processOrderReduce](const Order &order) {
    std::visit(help::overloaded{processOrderAdd, processOrderReduce}, order);
  };

  internal::loop(process_orders);
}
} // namespace obp

#endif
