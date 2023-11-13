#include <iostream>

#include "Lexer.h"

int main() {
    std::string Expression = "3 + \"hello\" = true; x = false; for if while";
    
    Lexer Lexer(Expression);
    Token Token;

    while (Token.Type != TokenType::END_OF_FILE) {
        Token = Lexer.GetNextToken();

        switch (Token.Type) {
            case TokenType::INTEGER:
                std::cout << "INTEGER";
                break;
            case TokenType::STRING:
                std::cout << "STRING";
                break;
            case TokenType::BOOLEAN:
                std::cout << "BOOLEAN";
                break;
            case TokenType::IDENTIFIER:
                std::cout << "IDENTIFIER";
                break;
            case TokenType::PLUS:
                std::cout << "PLUS";
                break;
            case TokenType::MINUS:
                std::cout << "MINUS";
                break;
            case TokenType::MULTIPLY:
                std::cout << "MULTIPLY";
                break;
            case TokenType::DIVIDE:
                std::cout << "DIVIDE";
                break;
            case TokenType::EQUALS:
                std::cout << "EQUALS";
                break;
            case TokenType::SEMICOLON:
                std::cout << "SEMICOLON";
                break;
            case TokenType::END_OF_FILE:
                std::cout << "END_OF_FILE";
                break;
            case TokenType::INVALID:
                std::cout << "INVALID";
                break;
        }

        std::cout << ", Value: " << Token.Value << std::endl;
    }

    return 0;
}