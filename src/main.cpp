#include "InputReader.hpp"
#include "OrderFollower.hpp"

#include <iostream>
#include <sstream>

static std::string
usage(const char* executable_name)
{
  std::stringstream text;
  text << "\nusage: " << executable_name << " <target_size>\n\n";

  text
    << "Pricer, that analyzes such a log file. Pricer takes one command-line\n"
       "argument: target-size. Pricer then reads a market data log on\n"
       "standard input. As the book is modified,Pricer prints (on standard\n"
       "output) the total expense you would incur if you bought target-size\n"
       "shares (by taking as many asks as necessary, lowest first), and the\n"
       "total income you would receive if you sold target-size shares (by\n"
       "hitting as many bids as necessary, highest first). Each time the\n"
       "income or expense changes, it prints the changed value.";
  return text.str();
}

static std::size_t
parse_target_size(const char* executable_name, const char* target_size)
{
  try {
    const auto value = std::stoll(target_size);
    if (value > 0) {
      return value;
    } else {
      std::cerr << "target_size must be strictly positive. Argument provided: "
                << target_size << '\n';
    }
  } catch (const std::invalid_argument& exception) {
    std::cerr << "Cannot deduce target_size. Argument provided: " << target_size
              << '\n'
              << "Error: " << exception.what() << '\n';

  } catch (const std::out_of_range& exception) {
    std::cerr << "target_size is out of range. Argument provided: "
              << target_size << '\n'
              << "Error: " << exception.what() << '\n';
  }
  std::cerr << usage(executable_name) << '\n';
  std::exit(EXIT_FAILURE);
}

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << usage(argv[0]) << '\n';
    return EXIT_FAILURE;
  }

  const auto target_size = parse_target_size(argv[0], argv[1]);
  std::cout << "target_size: " << target_size << '\n';

  obp::OrderFollower follower;

  while (!std::cin.eof()) {
    const auto order = obp::read_one(std::cin);
    if (order) {
      std::cout << *order << '\n';

      switch (order->type) {
        case obp::OrderType::AddOrder:
          std::cout << "added?: " << follower.add(order->data.add) << '\n';
          break;
        case obp::OrderType::ReduceOrder:
          const auto remaining_size = follower.reduce(order->data.reduce);
          if (remaining_size) {
            std::cout << "reduce to: " << *remaining_size << '\n';
          } else {
            std::cout << "Not there.\n";
          }
          break;
      }

    } else {
      std::cerr << "Cannot read one order\n";
    }
  }

  return EXIT_SUCCESS;
}
