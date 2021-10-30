CXX ?= clang++
CXXFLAGS += -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3
LDFLAGS += -fsanitize=address

OBJ := awk.o parse.o

awk: $(OBJ)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

clean:
	$(RM) *.o awk
.PHONY: clean
