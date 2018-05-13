#ifndef SRC_TIMER_HPP
#define SRC_TIMER_HPP

#include <chrono>

namespace help {
class Timer {
public:
  void print_elapsed_time() noexcept {
    const std::chrono::nanoseconds elapsed_time =
        std::chrono::system_clock::now() - m_start;

    std::cout.imbue(std::locale(""));

    std::cout << "Elapsed time (ns): " << elapsed_time.count() << '\n';
  }

private:
  std::chrono::time_point<std::chrono::system_clock> m_start =
      std::chrono::system_clock::now();
};
} // namespace help

#endif
