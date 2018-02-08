#include "InputReader.hpp"
#include "PricerOutput.hpp"

#include <iostream>

int
main()
{
  obp::PricerOutput po = { 1,
                           obp::Side::Bid,
                           std::make_optional<obp::Price>(2.12, 100) };
  std::cout << po << '\n';

  while (!std::cin.eof()) {
    const auto order = obp::read_one(std::cin);
    if (order) {
      std::cout << *order << '\n';
    } else {
      return 1;
    }
  }
  return 0;
}
