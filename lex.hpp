#pragma once
#include "types.hpp"
#include <string>

void dumptokens(const std::vector<Token>& tokens);
std::vector<Token> lex(const std::string& s);
