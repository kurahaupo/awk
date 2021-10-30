CXX ?= clang++
CXXFLAGS += -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3
LDFLAGS += -fsanitize=address

awk: awk.o parse.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) *.o awk
.PHONY: clean
