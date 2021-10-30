CXX ?= clang++
CXXFLAGS += -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3 -MMD -MP
LDFLAGS += -fsanitize=address

OBJ := awk.o parse.o

all: awk compile_flags.txt

awk: $(OBJ)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

$(OBJ): Makefile

compile_flags.txt: Makefile
	printf "%s\n" $(CXXFLAGS) >$@

clean:
	$(RM) *.o *.d awk compile_flags.txt

-include $(OBJ:.o=.d)

.PHONY: clean
