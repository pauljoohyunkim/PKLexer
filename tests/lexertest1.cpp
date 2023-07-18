#include "../src/pklexer.hpp"
#include <vector>
#include <utility>

enum TokenType
{
    TT_INT, TT_PLUS
};

int main()
{
    std::vector<std::pair<std::string, TokenType>> r_to_t = 
    {
        {"[0-9]+", TT_INT},
        {"\\+", TT_PLUS}
    };

    PKLexer<TokenType> lexer ("1 + 2 p \n 1", r_to_t);
    //lexer.setRegexTokenTypePairs(r_to_t);
    lexer.tokenize();

    auto tokens = lexer.getTokens();

    return 0;
}

template class PKLexer<TokenType>;
