#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <utility>
#include "pklexer.hpp"
#include "tokens.hpp"

static const std::vector<std::pair<std::string, TokenType>> regexToTokenType = 
{
    {"\\+", TT_PLUS},
    {"-", TT_MINUS},
    {"\\*", TT_STAR},
    {"/", TT_SLASH},
    {"[0-9]+", TT_INTEGER_LITERAL},
    {"([0-9]*\\.[0-9]+|[0-9]+\\.[0-9]*)", TT_DOUBLE_LITERAL},
    {"(true|false)", TT_BOOL_LITERAL}
};

void PKLexer::tokenize()
{
    while (isAtEnd() == false)
    {
        // Check if new line, then advance
        if (codetext[pos] == '\n')
        {
            line++;
            advance();
            continue;
        }

        // Comment by #
        if (codetext[pos] == '#')
        {
            advanceUntil('\n');
            continue;
        }

        if (isWhitespace())
        {
            advance();
            continue;
        }

        // Maximum munch rule
        bool matched { false };
        unsigned int matchLength { 0 };
        std::string matchRawString {};
        TokenType matchTokenType;
        for (auto entry : regexToTokenType)
        {
            auto regexstring { entry.first };
            auto tt { entry.second };
            std::cmatch cm;

            // Only match if it's at the beginning of the truncated code.
            auto tokenfilterstring = "^" + regexstring;
            std::regex tokenfilter(tokenfilterstring);

            // Regex match from truncated code (or rather, offset-ed code)
            matched = std::regex_search(codetext.c_str() + pos, cm, tokenfilter) || matched;

            // If match, compare with previous match for maximum munch
            if (cm.size() && matchLength < cm.length(0))
            {
                matchLength = cm.length(0);
                matchTokenType = tt;
                matchRawString = cm.str(0);
            }
        }
        tokens.push_back(Token(matchTokenType, matchRawString, line));
        advance(matchLength);
    }
    tokens.push_back(Token(TT_EOF, "", line));
}

void PKLexer::advanceUntil(char c)
{
    while (isAtEnd() == false && codetext[pos] != c)
    {
        if (codetext[pos] == '\n')
        {
            line++;
        }
        advance();
    }
}

bool PKLexer::isWhitespace()
{
    std::string s {codetext[pos]};
    std::regex whitespaceFilter { "\\s" };
    std::smatch sm;
    return std::regex_match(s, sm, whitespaceFilter);
}
