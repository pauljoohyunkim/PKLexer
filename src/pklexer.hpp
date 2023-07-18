#ifndef PKLEXER_HPP
#define PKLEXER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <utility>

template <class TokenType>
class Token
{
    public:
        Token<TokenType>(TokenType atokentype, std::string arawtext, unsigned int aline)
        { tokentype = atokentype; rawtext = arawtext; line = aline; }

    private:
        TokenType tokentype;
        std::string rawtext;
        unsigned int line { 1 };

};

template <class TokenType>
class PKLexer
{
    public:
        // Constructor
        PKLexer(std::string code, std::vector<std::pair<std::string, TokenType>> regexTokenTypePairVector)
        { codetext = code; init(); setRegexTokenTypePairs(regexTokenTypePairVector); }

        // Common initialization function
        void init() { pos = 0; line = 1; codelength = codetext.length(); }

        // Tokenize
        void tokenize()
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

                if (matched == true)
                {
                tokens.push_back(Token<TokenType>(matchTokenType, matchRawString, line));
                advance(matchLength);
                }
                else
                {
                    addErrorLine();
                    std::cerr << "Unrecognized token at line " << line << std::endl;
                    advanceUntil('\n');
                    continue;
                }
            }
        }

        // Return tokens
        std::vector<Token<TokenType>> getTokens() { return tokens; }

    private:
        std::string codetext {};
        unsigned int codelength { 0 };
        unsigned int pos { 0 };
        std::vector<Token<TokenType>> tokens {};
        unsigned int line { 1 };
        std::vector<std::pair<std::string, TokenType>> regexToTokenType;
        std::vector<unsigned int> errorLines {};

        // Helpers:
        bool isAtEnd() { return pos >= codelength; }
        void advance(unsigned int n=1) { pos = pos + n; }
        void advanceUntil(char c)
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
        bool isWhitespace()
        {
            std::string s {codetext[pos]};
            std::regex whitespaceFilter { "\\s" };
            std::smatch sm;
            return std::regex_match(s, sm, whitespaceFilter);
        }
        void setRegexTokenTypePairs(std::vector<std::pair<std::string, TokenType>> regexTokenTypePairVector)
        {
            regexToTokenType = regexTokenTypePairVector;
        }
        void addErrorLine() { errorLines.push_back(line); }
};

#endif  // PKLEXER_HPP
