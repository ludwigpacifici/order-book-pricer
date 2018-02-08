#include "Order.hpp"
#include "PricerOutput.hpp"

#include <iostream>

int
main()
{
  obp::Order o1(obp::OrderType::AddOrder,
                obp::AddOrder{ 1, "a", obp::Side::Ask, { 3 }, { 4 } });
  std::cout << o1 << '\n';

  obp::Order o2(obp::OrderType::ReduceOrder, obp::ReduceOrder{ 1, "a", { 2 } });

  std::cout << o2 << '\n';

  obp::PricerOutput po = { 1,
                           obp::Side::Bid,
                           std::optional<obp::Price>({ 2 }) };
  std::cout << po << '\n';

  return 0;
}
