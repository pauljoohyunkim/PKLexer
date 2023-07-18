#include "tokens.hpp"
#include "../src/pklexer.hpp"
#include <vector>
#include <utility>
#include <string>

int main()
{
    // Here is the code you want to tokenize.
    std::string code {"1 + 2"};

    // Here is the relation between regular expression and the token type.
    std::vector<std::pair<std::string, TokenType>> regexTokenTypePairs = 
    {
        {"[0-9]+", INTEGER_LITERAL},
        {"\\+", OPERATION_PLUS}
    };

    // Finally tokenization step!
    PKLexer<TokenType> lexer { code, regexTokenTypePairs };
    lexer.tokenize();

    // Here is a vector of Tokens
    auto tokens = lexer.getTokens();

    return 0;
}