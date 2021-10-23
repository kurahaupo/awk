CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3
all: awk
format:
	clang-format -i *.cpp
.PHONY: format
