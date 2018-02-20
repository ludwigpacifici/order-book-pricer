#ifndef SRC_OVERLOADED_HPP
#define SRC_OVERLOADED_HPP

namespace help {
// Helper to std::visit a variant
// http://en.cppreference.com/w/cpp/utility/variant/visit
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...)->overloaded<Ts...>;
} // namespace help

#endif
