#pragma once
#include <string>
#include <variant>

enum Punct : int;
enum Keyword : int;
using Number = double; // maybe bignums in the future?
struct Identifier : std::string { using std::string::string; };
struct Regex      : std::string { using std::string::string; };
struct String     : std::string {
    using std::string::string;
    static String unescape(String s);
};

using Token = std::variant<Identifier, Keyword, Number, String, Regex, Punct>;
