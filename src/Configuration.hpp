#ifndef SRC_CONFIGURATION_HPP
#define SRC_CONFIGURATION_HPP

#include <cstddef>

namespace obp {
enum class OutputFormat { Json, Compact };

constexpr auto g_format = OutputFormat::Compact;

constexpr std::size_t g_price_factor = 100;

} // namespace obp

#endif
