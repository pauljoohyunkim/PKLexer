# PKLexer
A simple lexer for C++.

This lexer (generator) attempts to be the simplest lexer generators that can be easily integrated into your project.

Note that this is hastily constructed at the moment, so expect a lot of change!

## Quickstart Guide:
To use PKLexer, just include **src/pklexer.hpp** onto your project.

We will be going over the example in the **sample** directory.

Suppose you want to get a lexer that can tokenize the following:
```
1 + 2
```
We need to be able to recognize integers and the plus sign.

Define the token types in **tokens.hpp**:
```
enum TokenType
{
    INTEGER_LITERAL,
    OPERATION_PLUS
};
```
Note that we can recognize the tokens by the following regular expressions:
```
/*
INTEGER_LITERAL: [0-9]+,
OPERATION_PLUS : +
*/
```
We are actually almost done!

Consider the following **sample.cpp**:
```
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
```
Compile this program by:
```
# Either
g++ -g -Wall sample.cpp -o sample
# or if you have make:
make
```
then you can set a breakpoint at the *return 0* statement and see if it worked or not.

## Notes
Currently, there is not much to it.
Plans at the moment are:
* Allow strings other than # for comment.
* Allow multiline comments
