CXX ?= clang++
CXXFLAGS += -std=c++20 -Wall -Wextra -fsanitize=address -ggdb3 -MMD -MP
LDFLAGS += -fsanitize=address

OBJ := awk.o parse.o

awk: $(OBJ)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

$(OBJ): Makefile

clean:
	$(RM) *.o *.d awk

-include $(OBJ:.o=.d)

.PHONY: clean
