#include "AddOrder.hpp"
#include "PricerOutput.hpp"
#include "ReduceOrder.hpp"

#include <iostream>

int
main()
{
  obp::AddOrder ao = { 1, "a", obp::Side::Ask, { 3 }, { 4 } };
  std::cout << ao << '\n';

  obp::ReduceOrder ro = { 1, "a", { 2 } };
  std::cout << ro << '\n';

  obp::PricerOutput po = { 1,
                           obp::Side::Bid,
                           std::optional<obp::Price>({ 2 }) };
  std::cout << po << '\n';

  return 0;
}
