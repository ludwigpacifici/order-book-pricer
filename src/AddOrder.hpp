#pragma once

#include "Configuration.hpp"
#include "Price.hpp"
#include "Quantity.hpp"
#include "Side.hpp"

#include <ctime>
#include <string>

namespace obp {
struct AddOrder
{
  std::time_t timestamp;
  std::string order_id;
  Side side;
  Price price;
  Quantity size;
};

std::ostream&
json(std::ostream& stream, const AddOrder& data)
{
  return stream << "{"
                << "\"timestamp\": " << data.timestamp << ", "
                << "\"order_id\": \"" << data.order_id << "\", "
                << "\"side\": \"" << data.side << "\", "
                << "\"price\": " << data.price << ", "
                << "\"size\": " << data.size << "}";
}

std::ostream&
compact(std::ostream& stream, const AddOrder& data)
{
  return stream << data.timestamp << " " << data.order_id << " " << data.side
                << " " << data.price << " " << data.size;
}

std::ostream&
operator<<(std::ostream& stream, const AddOrder& data)
{
  switch (config::g_output_format) {
    case config::OutputFormat::Compact:
      return compact(stream, data);
    case config::OutputFormat::Json:
      return json(stream, data);
    default:
      return compact(stream, data);
  }
}
}
