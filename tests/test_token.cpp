#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "../include/doctest.h"
#include <sstream>
#include "../src/token.h"

TEST_CASE("Token creation and attributes") {
    // Testando a criação de um Token e seus atributos
    Token token(TokenType::NUMI, "123", 1, 5);

    REQUIRE(token.type == TokenType::NUMI);
    REQUIRE(token.lexema == "123");
    REQUIRE(token.linha == 1);
    REQUIRE(token.coluna == 5);
}
TEST_CASE("reconhece literal string") {
    // Testando a criação de um Token e seus atributos
    Token token(TokenType::LITERAL, "\"essa é uma string literal\"", 1, 5);

    REQUIRE(token.type == TokenType::LITERAL);
    REQUIRE(token.lexema == "\"essa é uma string literal\"");
    REQUIRE(token.linha == 1);
    REQUIRE(token.coluna == 5);
}

TEST_CASE("TokenType values") {
    // Testando valores de TokenType
    REQUIRE(static_cast<int>(TokenType::NUMI) == 0);
    REQUIRE(static_cast<int>(TokenType::SE) != static_cast<int>(TokenType::ENQUANTO));
}