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
    std::istringstream iss(line);
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

inline void run(obp::Quantity target_size) {
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
      bookBuy.add(add_order.price, add_order.size);

#ifdef DEBUG
      std::cout << "order: " << add_order << '\n';
      std::cout << "BookBuy: " << bookBuy << '\n';
#endif

      if (const auto output =
              pricerBuy.price(add_order.timestamp, obp::Side::Ask, bookBuy,
                              add_order.price, target_size);
          output) {
        std::cout << *output << '\n';
      }
      break;

    case obp::Side::Ask:
      bookSell.add(add_order.price, add_order.size);

#ifdef DEBUG
      std::cout << "order: " << add_order << '\n';
      std::cout << "bookSell: " << bookSell << '\n';
#endif

      if (const auto output =
              pricerSell.price(add_order.timestamp, obp::Side::Bid, bookSell,
                               add_order.price, target_size);
          output) {
        std::cout << *output << '\n';
      }
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
        case obp::Side::Bid: {
          const auto remaining_quantity =
              bookBuy.reduce(anonymous_order->price, reduce_order.size);

#ifdef DEBUG
          std::cout << "order: " << reduce_order << '\n';
          std::cout << "BookBuy: " << bookBuy << '\n';
#endif

          if (const auto output = pricerBuy.price(
                  reduce_order.timestamp, obp::Side::Ask, bookBuy,
                  anonymous_order->price, remaining_quantity, target_size);
              output) {
            std::cout << *output << '\n';
          }
        } break;

        case obp::Side::Ask: {
          const auto remaining_quantity =
              bookSell.reduce(anonymous_order->price, reduce_order.size);

#ifdef DEBUG
          std::cout << "order: " << reduce_order << '\n';
          std::cout << "bookSell: " << bookSell << '\n';
#endif

          if (const auto output = pricerSell.price(
                  reduce_order.timestamp, obp::Side::Bid, bookSell,
                  anonymous_order->price, remaining_quantity, target_size);
              output) {
            std::cout << *output << '\n';
          }
        } break;

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
