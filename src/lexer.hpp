#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "tokens.hpp"

class Lexer
{
    public:
        // Constructor
        Lexer(std::string code) { codetext = code; init(); }

        // Common initialization function
        void init() { pos = 0; line = 1; codelength = codetext.length(); }

        // Tokenize
        void tokenize();

        // Return tokens
        std::vector<Token> getTokens() { return tokens; }

    private:
        std::string codetext {};
        unsigned int codelength { 0 };
        unsigned int pos { 0 };
        std::vector<Token> tokens {};
        unsigned int line { 1 };

        // Helpers:
        bool isAtEnd() { return pos >= codelength; }
        void advance(unsigned int n=1) { pos = pos + n; }
        void advanceUntil(char c);
        bool isWhitespace();

};

#endif  // LEXER_HPP
