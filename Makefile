CXX ?= clang++
CXXFLAGS += -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3
LDFLAGS += -fsanitize=address

# this should be able to use the implicit rule but make tries to call
# cc awk.o parse.o -o awk
# which fails with ugly link errors
awk: awk.o parse.o # headers?
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o awk
.PHONY: clean
