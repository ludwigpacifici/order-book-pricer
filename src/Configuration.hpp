#pragma once

namespace obp::config {
enum class OutputFormat
{
  Compact,
  Json
};

constexpr auto g_output_format = OutputFormat::Json;
}
