#include "types.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <iostream>
#include <cstring>

struct parse_error : std::logic_error {
    parse_error(std::string description, std::string problem,
                size_t pos = 0, size_t count = std::string::npos) :
        std::logic_error(description + " <" + problem.substr(pos, count) + ">") {}
};

using std::vector, std::string, std::map;

enum Punct : int {
    PLUSPLUS  , PLUSEQ , PLUS  ,
    MINUSMINUS, MINUSEQ, MINUS ,
                TIMESEQ, TIMES ,
                DIVEQ  , DIV   ,
                PERCEQ , PERC  ,

    ANDAND    , ANDEQ  , AND   ,
    OROR      , OREQ   , OR    ,
                XOREQ  , XOR   ,

    LTLT      , LTEQ   , LT    ,
    GTGT      , GTEQ   , GT    ,
    EQEQ      ,          EQ    ,
                NEQ    , EXCLAM,

    LBRK      , RBRK   ,
    LPAR      , RPAR   ,
    LBRAC     , RBRAC  ,

    QUESTION  , COLON  , TILDE  ,
    SEMICOLON , COMMA  , DOLLAR ,
};

namespace {

map<Punct, string> punctstringmap = {
    { PLUSPLUS  , "++" }, { PLUSEQ , "+=" }, { PLUS  , "+" },
    { MINUSMINUS, "--" }, { MINUSEQ, "-=" }, { MINUS , "-" },
                          { TIMESEQ, "*=" }, { TIMES , "*" },
                          { DIVEQ  , "/=" }, { DIV   , "/" },
                          { PERCEQ , "%=" }, { PERC  , "%" },
                                                           
    { ANDAND    , "&&" }, { ANDEQ  , "&=" }, { AND   , "&" },
    { OROR      , "||" }, { OREQ   , "|=" }, { OR    , "|" },
                          { XOREQ  , "^=" }, { XOR   , "^" },
                                                           
    { LTLT      , "<<" }, { LTEQ   , "<=" }, { LT    , "<" },
    { GTGT      , ">>" }, { GTEQ   , ">=" }, { GT    , ">" },
    { EQEQ      , "==" },                    { EQ    , "=" },
                          { NEQ    , "!=" }, { EXCLAM, "!" },

    { LBRK      , "["  }, { RBRK   , "]"  },
    { LPAR      , "("  }, { RPAR   , ")"  },
    { LBRAC     , "{"  }, { RBRAC  , "}"  },
                                     
    { QUESTION  , "?"  }, { COLON  , ":"  }, { TILDE , "~" },
    { SEMICOLON , ";"  }, { COMMA  , ","  }, { DOLLAR, "$" },
};

map<string, Punct> stringpunctmap = {
    { "++", PLUSPLUS   }, { "+=", PLUSEQ  }, { "+", PLUS   },
    { "--", MINUSMINUS }, { "-=", MINUSEQ }, { "-", MINUS  },
                          { "*=", TIMESEQ }, { "*", TIMES  },
                          { "/=", DIVEQ   }, { "/", DIV    },
                          { "%=", PERCEQ  }, { "%", PERC   },
                                                           
    { "&&", ANDAND     }, { "&=", ANDEQ   }, { "&", AND    },
    { "||", OROR       }, { "|=", OREQ    }, { "|", OR     },
                          { "^=", XOREQ   }, { "^", XOR    },
                                                           
    { "<<", LTLT       }, { "<=", LTEQ    }, { "<", LT     },
    { ">>", GTGT       }, { ">=", GTEQ    }, { ">", GT     },
    { "==", EQEQ       },                    { "=", EQ     },
                          { "!=", NEQ     }, { "!", EXCLAM },
                                                          
    { "[" , LBRK       }, { "]" , RBRK    },              
    { "(" , LPAR       }, { ")" , RPAR    },              
    { "{" , LBRAC      }, { "}" , RBRAC   },              
                                                          
    { "?" , QUESTION   }, { ":" , COLON   }, { "~", TILDE  },
    { ";" , SEMICOLON  }, { "," , COMMA   }, { "$", DOLLAR },
};

}; // namespace

enum Keyword : int {
    BEGIN, END,

    BREAK, CONTINUE, NEXT, RETURN,
    DO, WHILE,
    FOR, IN,
    IF, ELSE,
    SWITCH, CASE,
    EXIT,

    DELETE,

    FUNCTION,

    GETLINE,
    PRINT, PRINTF,
};

namespace {
map<string, Keyword> keywordstringmap = {
    { "BEGIN"   , BEGIN    }, { "END"     , END      },

    { "break"   , BREAK    }, { "continue", CONTINUE },
    { "next"    , NEXT     }, { "return"  , RETURN   },
    { "do"      , DO       }, { "while"   , WHILE    },
    { "for"     , FOR      }, { "in"      , IN       },
    { "if"      , IF       }, { "else"    , ELSE     },
    { "switch"  , SWITCH   }, { "case"    , CASE     },
    { "exit"    , EXIT     },

    { "delete"  , DELETE   },

    { "function", FUNCTION }, { "func"    , FUNCTION },

    { "getline" , GETLINE  },
    { "print"   , PRINT    }, { "printf"  , PRINTF   },
};

map<Keyword, string> stringkeywordmap = {
    { BEGIN   , "BEGIN"    }, { END     , "END"      },
                                                    
    { BREAK   , "break"    }, { CONTINUE, "continue" },
    { NEXT    , "next"     }, { RETURN  , "return"   },
    { DO      , "do"       }, { WHILE   , "while"    },
    { FOR     , "for"      }, { IN      , "in"       },
    { IF      , "if"       }, { ELSE    , "else"     },
    { SWITCH  , "switch"   }, { CASE    , "case"     },
    { EXIT    , "exit"     },                       
                                                    
    { DELETE  , "delete"   },                       
                                                    
    { FUNCTION, "function" }, { FUNCTION, "func"     },
                                                    
    { GETLINE , "getline"  },                       
    { PRINT   , "print"    }, { PRINTF  , "printf"   },
};

}; // namespace

String String::unescape(String s) {
    String ret;
    map<char, char> escapes {
        { 'v', '\v' },
        { 'f', '\f' },
        { 'r', '\r' },
        { 'n', '\n' },
        { 't', '\t' },
        { '"', '"' },
        { '\\', '\\' },
    };

    for (size_t i = 0; i < s.length(); i++) {
        // not escaped
        if (s[i] != '\\') {
            ret += s[i];
            continue;
        }

        i++;
        if (i == s.length())
            throw parse_error{"backslash not allowed at end of string"};    // TODO: handle line continuation

        // simple escape
        if (escapes.find(s[i]) != escapes.end()) {
            ret += escapes[s[i]];
            continue;
        }

        template <T, U> T convert (auto conversionfunc, auto maxchars, auto& s, auto& i) {
            U c = 0;
            if (!conversionfunc(c, s[i]))
                    throw parse_error{"this doesn't look like a number?", s.substr(i)};
            for (auto q = 1 ; q < maxchars && conversionfunc(c, s[++i]); q++) {}
            return c;
        }

        auto conv_hex = [](auto& a, auto c) {
                auto r = a;                             // important that r have the same type as acc.
                r <<= 4;
                if (r >> 4 != a) return false;          // result won't fit
                if (!isxdigit(c)) return false;
                     if (islower(c)) c -= 'a'-10;
                else if (isupper(c)) c -= 'A'-10;
                else c -= '0';
                a = r | c;
                return true;
            };

        if (s[i] == 'x') {
            i++;
            ret += convert<char, uint8_t>(conv_hex, 2, s, i);
            continue;
        }
        
        
        if (s[i] == 'u') {
            ++i;
            auto x = convert<int32_t, uint16_t>(conv_hex, 4, s, i);
            ret += wchar2utf8(x);
            continue;
        }
        if (s[i] == 'U') {
            ++i;
            auto x = convert<int32_t, uint32_t>(conv_hex, 8, s, i);
            ret += wchar2utf8(x);
            continue;
        }
        
        auto conv_oct = [](auto& a, auto c) {           // will throw if first is not octal digit
                    auto r = a;
                    r <<= 3;
                    if (r >> 3 != a) return false;      // result won't fit
                    if (!isdigit(c)) return false;      // not a digit
                    if (c > '7') return false;          // not an octal digit
                    a = r | c - '0';
                    return true;
                };

        if (isdigit(s[i])) {
            ret += convert<char, uint8_t>(conv_oct, 3, s, i);
            continue;
        }
                throw parse_error{"unknown backslash sequence?", s.substr(i)};
        }

    return ret;
}

std::vector<Token> lex(const string& s) {
    std::vector<Token> tokens;

    for (size_t i = 0; s[i]; i++) {
        auto start = i;
        Token tok;

        if (isspace(s[i]))
            continue;

        else if (s[i] == '#') {
            while (s[i] && s[i] != '\n')
                i++;
        }

        // identifier/keyword
        else if (isalpha(s[i])) {
            while (isalnum(s[i+1]))
                i++;

            string tmp{ s.begin() + start, s.begin() + i + 1 };
            if (keywordstringmap.find(tmp) != keywordstringmap.end())
                tok = Keyword{keywordstringmap[tmp]};
            else
                tok = Identifier{tmp.data(), tmp.size()};
        }

        // number
        else if (isdigit(s[i])) {
            size_t end;
            auto d = std::stod(s.substr(i), &end);
            i += end - 1;
            tok = d;
        }

        // string
        else if (s[i] == '"') {
            for ( ; s[i+1] != '"' && s[i+1] != '\0'; i++)
                if (s[i+1] == '\\' && s[i+2] != '\0')
                    i++;
            i++;
            if (s[i] == '"')
                tok = String::unescape(String{ s.begin() + start + 1, s.begin() + i });
            else
                throw parse_error{"unterminated string?", s, start};
        }

        // how the hell do you tell that a regex is not a division?

        // punctuation
        else {
            for (auto [p, str] : punctstringmap) {
                if (strncmp(s.c_str() + start, str.c_str(), str.size()) == 0) {
                    tok = p;
                    goto punctok;
                }
            }
            throw parse_error{"wtf is this?", s.substr(start)};
            punctok: ;
        }

        tokens.push_back(tok);
    }
    return tokens;
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void dumptokens(const std::vector<Token>& tokens) {
    std::cout << '[';
    std::vector<string> formats {
        // maybe something else in the future
        "\x1b[31m",
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[34m",
        "\x1b[35m",
        "\x1b[36m",
    };
    for (const auto& tok : tokens) {
        std::cout << " <" << formats[tok.index()];
        std::visit(overloaded {
                [](auto    arg) { std::cout << arg                  ; },
                [](Punct   arg) { std::cout << punctstringmap[arg]  ; },
                [](Keyword arg) { std::cout << stringkeywordmap[arg]; },
                }, tok);
        std::cout << "\x1b[m>";
    }
    std::cout << " ]\n";
}
