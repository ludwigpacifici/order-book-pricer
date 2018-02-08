#pragma once

#include <iostream>
#include <optional>

namespace obp {
enum class Side
{
  Bid,
  Ask
};

std::optional<Side>
side_from(char side)
{
  switch (side) {
    case 'B':
    case 'b':
      return Side::Bid;
    case 'S':
    case 's':
      return Side::Ask;
    default:
      std::cerr << "Invalid side: " << side
                << ", ASCII code: " << static_cast<int>(side) << '\n';
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
