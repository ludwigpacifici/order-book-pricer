#include "Configuration.hpp"
#include "Price.hpp"
#include "Side.hpp"

#include <ctime>
#include <string>

namespace obp {
struct PricerOutput
{
  std::time_t timestamp;
  Side action;
  std::optional<Price> total;
};

std::ostream&
json(std::ostream& stream, const PricerOutput& data)
{
  stream << "{"
         << "\"timestamp\": " << data.timestamp << ", "
         << "\"action\": " << data.action << ", "
         << "\"total\": ";

  if (data.total) {
    stream << *data.total;
  } else {
    stream << "NA";
  }
  return stream << "}";
}

std::ostream&
compact(std::ostream& stream, const PricerOutput& data)
{
  stream << data.timestamp << " " << data.action << " ";

  if (data.total) {
    return stream << *data.total;
  } else {
    return stream << "NA";
  }
}

std::ostream&
operator<<(std::ostream& stream, const PricerOutput& data)
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
