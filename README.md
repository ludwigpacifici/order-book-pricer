# order-book-pricer

Small project to play with C++17 and [FlameGraph](https://github.com/brendangregg/FlameGraph). See [`order-book-programming-problem.pdf`](https://github.com/ludwigpacifici/order-book-pricer/blob/master/order-book-programming-problem.pdf) for the problem definition.

## Prerequisites

* C++17 compiler. Tested with `g++ (GCC) 8.1.1 20180531` and `clang version 6.0.0 (tags/RELEASE_600/final)`
* [perf](https://perf.wiki.kernel.org/index.php/Main_Page)
* [FlameGraph](https://github.com/brendangregg/FlameGraph)
* Developed with Linux: `4.16.13-2-ARCH`

## Build

Use Makefile from the project root directory. Targets:

* `make` - compile the project in release mode. `-O2` flag is enabled.
* `make debug` - compile the project in debug mode. Optimisations are disabled `-O0` and debug symbols are available `-g`
* `make test` - run the tests
* `make perf` - generate the FlameGraph (in `tests` folder)
* `make time` - show the runtime timings.

## Other implementations

[dark_rusty_pool](https://github.com/petr-tik/dark_rusty_pool) is a Rust implementation by [petr-tik](https://github.com/petr-tik)
