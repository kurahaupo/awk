#include "types.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <iostream>
#include <cstring>

using std::vector, std::string, std::map;

enum Punct : int {
    PLUSPLUS  , PLUSEQ , PLUS  ,
    MINUSMINUS, MINUSEQ, MINUS ,
    TIMESTIMES, TIMESEQ, TIMES ,
    DIVDIV    , DIVEQ  , DIV   ,
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

    QUESTION  , COLON  , TILDE ,
    SEMICOLON , COMMA  , DOLLAR ,
};

namespace {
map<Punct, string> punctstringmap = {
    { PLUSPLUS  , "++" }, { PLUSEQ , "+=" }, { PLUS  , "+" },
    { MINUSMINUS, "--" }, { MINUSEQ, "-=" }, { MINUS , "-" },
    { TIMESTIMES, "**" }, { TIMESEQ, "*=" }, { TIMES , "*" },
    { DIVDIV    , "//" }, { DIVEQ  , "/=" }, { DIV   , "/" },
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
    { "**", TIMESTIMES }, { "*=", TIMESEQ }, { "*", TIMES  },
    { "//", DIVDIV     }, { "/=", DIVEQ   }, { "/", DIV    },
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

};

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

    for (size_t i = 0; s[i]; i++) {
        // not escaped
        if (s[i] != '\\') {
            ret += s[i];
        }

        // simple escape
        else if (escapes.find(s[i+1]) != escapes.end()) {
            ret += escapes[s[i+1]];
            i++;
        }

        // hex oct
        else {
            auto fromhex = [](auto old, auto c) {
                auto val = old << 4;
                if (c >= '0' && c <= '9') val |= c - '0';
                else if (c >= 'a' && c <= 'f') val |= c - 'a';
                else                           val |= c - 'A';
                return val;
            };
            auto fromoct = [](auto old, auto c) { return (old << 3) | (c - '0'); };

            auto isoctdigit = [](auto c) { return c >= '0' && c <= '7'; };

            auto convert = [&](auto acceptingfunc, auto conversionfunc, auto maxchars) {
                unsigned char c = 0;

                auto q = 0;
                for ( ; q < maxchars; q++) {
                    if (acceptingfunc(s[i])) {
                        c = conversionfunc(c, s[i++]);
                    }
                    else break;
                }
                if (q == 0)
                    throw std::logic_error(string{"this doesn't look like a number? <"}.append(s, i).append(">"));

                // next unparsed char is at i
                i--;

                return static_cast<char>(c);
            };

            i++;
            if (s[i] == 'x') {
                i++;
                ret += convert(isxdigit, fromhex, 2);
            }
            else if (isoctdigit(s[i]))
                ret += convert(isoctdigit, fromoct, 3);
            else
                throw std::logic_error(string{"unknown backslash sequence? <"}.append(s, i).append(">"));
        }
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
                throw std::logic_error(string{"unterminated string? <"}.append(s, start).append(">"));
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
            throw std::logic_error(string{"wtf is this? <"}.append(s, start).append(">"));
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
