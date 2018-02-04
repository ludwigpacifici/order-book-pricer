CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic -O2
SRC_FILES=$(wildcard *.cpp)
HDR_FILES=$(wildcard *.hpp)
BIN=order-book-tracker

all:
	$(CXX) $(CXXFLAGS) main.cpp -o order-book-tracker

clang_format:
	$(foreach file,$(HDR_FILES) $(SRC_FILES),clang-format -i $(file);)

cppcheck:
	$(foreach file,$(HDR_FILES) $(SRC_FILES),cppcheck -q --language=c++ --std=c++11 --enable=all --template=gcc $(file);)

clean:
	rm -f $(BIN)
