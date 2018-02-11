#pragma once

#include "Configuration.hpp"
#include "Quantity.hpp"

#include <ctime>
#include <string>

namespace obp {
struct ReduceOrder
{
  std::time_t timestamp;
  std::string order_id;
  Quantity size;
};

std::ostream&
json(std::ostream& stream, const ReduceOrder& data)
{
  return stream << "{"
                << "\"timestamp\": " << data.timestamp << ", "
                << "\"order_id\": \"" << data.order_id << "\", "
                << "\"size\": " << data.size << "}";
}

std::ostream&
compact(std::ostream& stream, const ReduceOrder& data)
{
  return stream << data.timestamp << " " << data.order_id << " " << data.size;
}

std::ostream&
operator<<(std::ostream& stream, const ReduceOrder& data)
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
