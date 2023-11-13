#pragma once

#include <cctype>
#include <iostream>
#include <map>

enum class TokenType {
    INTEGER,
    STRING,
    BOOLEAN,
    IDENTIFIER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EQUALS,
    SEMICOLON,
    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType Type;
    std::string Value;

     Token() : Type(TokenType::INVALID), Value("") {}  

    Token(TokenType t, const std::string& v = "") : Type(t), Value(v) {}
};

class Lexer {
private:
    //variables

    std::string Input;
    size_t Position;
    std::map<std::string, TokenType> Keywords;
    std::map<char, TokenType> Operators;
public:
    Lexer(const std::string &String) : Input(String), Position(0) {
        Keywords = {
            {"true", TokenType::BOOLEAN},
            {"false", TokenType::BOOLEAN}
        };

        Operators = {
            {'+', TokenType::PLUS},
            {'-', TokenType::MINUS},
            {'/', TokenType::DIVIDE},
            {'*', TokenType::MULTIPLY},
            {'=', TokenType::EQUALS},
            {';', TokenType::SEMICOLON}
        };
    }

   Token GetNextToken() {
        while (Position < Input.size() && std::isspace(Input[Position])) {
            Position++;
        }

        if (Position >= Input.size()) {
            return Token(TokenType::END_OF_FILE);
        }

        char CurrentChar = Input[Position];

        if (std::isdigit(CurrentChar)) {
            return ParseInteger();
        } else if (CurrentChar == '\"') {
            return ParseString();
        } else if (std::isalpha(CurrentChar)) {
            return ParseIdentifierOrKeyword();
        } else if (Operators.find(CurrentChar) != Operators.end()) {
            TokenType OperatorType = Operators[CurrentChar];
            Position++;
            return Token(OperatorType, std::string(1, CurrentChar));
        } else {
            return Token(TokenType::INVALID, std::string(1, CurrentChar));
        }
    }  

private:
    //functions... lol
    Token ParseInteger() {
      std::string Result;
        while (Position < Input.size() && (std::isdigit(Input[Position]) || Input[Position] == '.')) {
            Result += Input[Position];
            Position++;
        }
        return Token(TokenType::INTEGER, Result);
    }


    Token ParseString() {
        Position++; // Skip opening quote
        std::string Result;
        while (Position < Input.size() && Input[Position] != '\"') {
            Result += Input[Position];
            Position++;
        }
        Position++; // Skip closing quote
        return Token(TokenType::STRING, Result);
    }

    Token ParseIdentifierOrKeyword() {
        std::string Result;
        while (Position < Input.size() && (std::isalnum(Input[Position]) || Input[Position] == '_')) {
            Result += Input[Position];
            Position++;
        }

        auto it = Keywords.find(Result);
        if (it != Keywords.end()) {
            return Token(it->second, Result);
        } else {
            return Token(TokenType::IDENTIFIER, Result);
        }
    }
};