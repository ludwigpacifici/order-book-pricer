CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -Wpedantic
RELEASE=-O2
DEBUG=-g -O0
SRC_FILES=$(wildcard *.cpp)
HDR_FILES=$(wildcard *.hpp)
BIN=order-book-pricer

all: release

release:
	$(CXX) $(CXXFLAGS) $(RELEASE) main.cpp -o $(BIN)

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG) -DDEBUG main.cpp -o $(BIN)

clang_format:
	$(foreach file,$(HDR_FILES) $(SRC_FILES),clang-format -i $(file);)

clang_tidy:
	clang-tidy -config='' main.cpp -- -std=c++17

cppcheck:
	$(foreach file,$(SRC_FILES),cppcheck -q --language=c++ --std=c++11 --enable=all --template=gcc $(file);)

clean:
	rm -f $(BIN)

test:
	make --directory=.. $@

perf:
	make --directory=.. $@

time:
	make --directory=.. $@
