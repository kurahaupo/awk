CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3
LDFLAGS = -fsanitize=address

# this should be able to use the implicit rule but make tries to call
# cc awk.o lex.o -o awk
# which fails with ugly link errors
awk: awk.o lex.o # headers?
	$(CXX) $^ $(LDFLAGS) -o $@

format:
	clang-format -i *.cpp

clean:
	rm -f *.o awk
.PHONY: format clean
