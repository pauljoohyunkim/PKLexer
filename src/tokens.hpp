#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>


enum TokenType
{
    // Operations,
    TT_PLUS, TT_MINUS, TT_STAR, TT_SLASH,

    // Literals
    TT_INTEGER_LITERAL, TT_DOUBLE_LITERAL, TT_BOOL_LITERAL,

    // End of file token
    TT_EOF
};

class Token
{
    public:
        Token(TokenType atokentype, std::string arawtext, unsigned int aline)
        { tokentype = atokentype; rawtext = arawtext; line = aline; }

    private:
        TokenType tokentype;
        std::string rawtext;
        unsigned int line { 1 };

};


#endif
