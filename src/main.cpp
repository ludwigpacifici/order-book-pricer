#include "Core.hpp"

static std::string usage(const char *executable_name) {
  std::stringstream text;
  text << "\nusage: " << executable_name << " [<target_size>|--dry-run]\n\n";

  text
      << "Pricer, that analyzes such a log file. Pricer takes one "
         "command-line\n"
         "argument: target-size. Pricer then reads a market data log on\n"
         "standard input. As the book is modified,Pricer prints (on standard\n"
         "output) the total expense you would incur if you bought target-size\n"
         "shares (by taking as many asks as necessary, lowest first), and the\n"
         "total income you would receive if you sold target-size shares (by\n"
         "hitting as many bids as necessary, highest first). Each time the\n"
         "income or expense changes, it prints the changed value.";
  return text.str();
}

static obp::Quantity parse_target_size(const char *executable_name,
                                       const char *target_size) {
  try {
    const auto value = std::stoll(target_size);
    if (value > 0) {
      return obp::Quantity(value);
    }

    std::cerr << "target_size must be strictly positive. Argument provided: "
              << target_size << '\n';

  } catch (const std::invalid_argument &exception) {
    std::cerr << "Cannot deduce target_size. Argument provided: " << target_size
              << '\n'
              << "Error: " << exception.what() << '\n';

  } catch (const std::out_of_range &exception) {
    std::cerr << "target_size is out of range. Argument provided: "
              << target_size << '\n'
              << "Error: " << exception.what() << '\n';
  }
  std::cerr << usage(executable_name) << '\n';
  std::exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << usage(argv[0]) << '\n';
    return EXIT_FAILURE;
  }

  if (std::string_view(argv[1]) == "--dry-run") {
    obp::run();
  } else {
    obp::run(parse_target_size(argv[0], argv[1]));
  }

  return EXIT_SUCCESS;
}
