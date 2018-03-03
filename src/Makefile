CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -Wpedantic -O2
SRC_FILES=$(wildcard *.cpp)
HDR_FILES=$(wildcard *.hpp)
BIN=order-book-pricer

all: compile

compile:
	$(CXX) $(CXXFLAGS) main.cpp -o $(BIN)

clang_format:
	$(foreach file,$(HDR_FILES) $(SRC_FILES),clang-format -i $(file);)

clang_tidy:
	clang-tidy -config='' main.cpp -- -std=c++17

cppcheck:
	$(foreach file,$(SRC_FILES),cppcheck -q --language=c++ --std=c++11 --enable=all --template=gcc $(file);)

clean:
	rm -f $(BIN)

test:
	make --directory=.. test
