#include "token.h"

std::string getTokenType(TokenType type) {
    static const std::string values[]{
        "IDENTIFIER", "INT",    "STRING",    "LBRACE",    "RBRACE",
        "LPAREN",     "RPAREN", "SEMICOLON", "ENDOFFILE", "EMPTY",
        "STAR",       "PLUS",   "MINUS",     "SLASH",     "EQUALS",
    };
    return values[type];
}
std::string getPrintableToken(Token *token) {
    std::string ret = "TOKEN(type: " + getTokenType(token->type) +
                      ", value: " + token->value + ")";
    return ret;
}
