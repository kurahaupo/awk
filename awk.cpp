#include <vector>
#include "types.hpp"
#include "parse.hpp"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        auto v = lex(argv[1]);
        dumptokens(v);
    }
    else {
        dumptokens(lex("$1    >     8 { print \"foobar\\x4x1baz\" }"));
        dumptokens(lex("\"ppp\\\".qqq \\x3007 \\06007\""));
        dumptokens(lex("function f() { while (1) break; meow moo }"));
    }
}
