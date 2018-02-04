#pragma once

#include <optional>
#include <ostream>

namespace obp {
enum class Side
{
  Bid,
  Ask
};

std::optional<Side>
side_from(char c)
{
  switch (c) {
    case 'B':
      return Side::Bid;
    case 'S':
      return Side::Ask;
    default:
      return std::nullopt;
  }
}

std::ostream&
json(std::ostream& stream, const Side& data)
{
  switch (data) {
    case Side::Bid:
      return stream << "Bid";
    case Side::Ask:
      return stream << "Ask";
    default:
      return stream << "Unknown Side";
  }
}

std::ostream&
compact(std::ostream& stream, const Side& data)
{
  switch (data) {
    case Side::Bid:
      return stream << 'B';
    case Side::Ask:
      return stream << 'S';
    default:
      return stream << "Unknown Side";
  }
}

std::ostream&
operator<<(std::ostream& stream, const Side& data)
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
