CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic
SRC_FILES=$(wildcard *.cpp)
HDR_FILES=$(wildcard *.hpp)

all:
	$(CXX) $(CXXFLAGS) main.cpp -o order-book-tracker

clang_format:
	$(foreach file,$(SRC_FILES),clang-format -i $(file);)
	$(foreach file,$(HDR_FILES),clang-format -i $(file);)
