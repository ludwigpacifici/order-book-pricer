#ifndef SRC_CONFIGURATION_HPP
#define SRC_CONFIGURATION_HPP

namespace obp {
enum class OutputFormat { Json, Compact };

constexpr auto g_format = OutputFormat::Compact;
} // namespace obp

#endif
