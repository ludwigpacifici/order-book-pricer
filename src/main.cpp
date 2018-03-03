#include "AnonymousBook.hpp"
#include "InputReader.hpp"
#include "OrderFollower.hpp"
#include "Pricer.hpp"

#include <iostream>
#include <sstream>

static std::string usage(const char *executable_name) {
  std::stringstream text;
  text << "\nusage: " << executable_name << " <target_size>\n\n";

  text
      << "Pricer, that analyzes such a log file. Pricer takes one "
         "command-line\n"
         "argument: target-size. Pricer then reads a market data log on\n"
         "standard input. As the book is modified,Pricer prints (on standard\n"
         "output) the total expense you would incur if you bought target-size\n"
         "shares (by taking as many asks as necessary, lowest first), and the\n"
         "total income you would receive if you sold target-size shares (by\n"
         "hitting as many bids as necessary, highest first). Each time the\n"
         "income or expense changes, it prints the changed value.";
  return text.str();
}

static obp::Quantity parse_target_size(const char *executable_name,
                                       const char *target_size) {
  try {
    const auto value = std::stoll(target_size);
    if (value > 0) {
      return obp::Quantity(value);
    }

    std::cerr << "target_size must be strictly positive. Argument provided: "
              << target_size << '\n';

  } catch (const std::invalid_argument &exception) {
    std::cerr << "Cannot deduce target_size. Argument provided: " << target_size
              << '\n'
              << "Error: " << exception.what() << '\n';

  } catch (const std::out_of_range &exception) {
    std::cerr << "target_size is out of range. Argument provided: "
              << target_size << '\n'
              << "Error: " << exception.what() << '\n';
  }
  std::cerr << usage(executable_name) << '\n';
  std::exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << usage(argv[0]) << '\n';
    return EXIT_FAILURE;
  }

  const auto target_size = parse_target_size(argv[0], argv[1]);

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
      // std::cout << "BookBuy: " << bookBuy << '\n';

      if (const auto output = pricerBuy.price(
              add_order.timestamp, obp::Side::Ask, bookBuy, target_size);
          output) {
        std::cout << *output << '\n';
      }
      break;

    case obp::Side::Ask:
      bookSell.add(add_order.price, add_order.size);
      // std::cout << "bookSell: " << bookSell << '\n';

      if (const auto output = pricerSell.price(
              add_order.timestamp, obp::Side::Bid, bookSell, target_size);
          output) {
        std::cout << *output << '\n';
      }
      break;

    default:
      std::cerr << "Unknown order add side: " << add_order.side << '\n';
      break;
    }
  };

  auto processOrderReduce = [&follower, &bookBuy, &bookSell, &pricerBuy,
                             &pricerSell, target_size](
                                const obp::ReduceOrder &reduce_order) {
    const auto anonymous_order = follower.reduce(reduce_order);

    switch (anonymous_order->side) {
    case obp::Side::Bid:
      bookBuy.reduce(anonymous_order->price, reduce_order.size);
      // std::cout << "BookBuy: " << bookBuy << '\n';

      if (const auto output = pricerBuy.price(
              reduce_order.timestamp, obp::Side::Ask, bookBuy, target_size);
          output) {
        std::cout << *output << '\n';
      }
      break;

    case obp::Side::Ask:
      bookSell.reduce(anonymous_order->price, reduce_order.size);
      // std::cout << "bookSell: " << bookSell << '\n';

      if (const auto output = pricerSell.price(
              reduce_order.timestamp, obp::Side::Bid, bookSell, target_size);
          output) {
        std::cout << *output << '\n';
      }
      break;

    default:
      std::cerr << "Not there.\n";
      break;
    }
  };

  while (!std::cin.eof()) {
    const auto order = obp::read_one(std::cin);
    if (order) {
      std::cout << "order: " << *order << '\n';
      std::visit(help::overloaded{processOrderAdd, processOrderReduce}, *order);
    } else {
      std::cerr << "Cannot read one order\n";
    }
  }

  return EXIT_SUCCESS;
}
