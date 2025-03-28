#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "../include/doctest.h"
#include "../src/lexer.cpp"

TEST_CASE("Reconhecimento strings basicas") {
    Lexer lexer(" imprimir(\"hello world\")");
    vector<Token> tokens = lexer.inicializa();
    REQUIRE(tokens[0].type == TokenType::IMPRIMIR);
    REQUIRE(tokens[0].lexema == "imprimir");
    
    REQUIRE(tokens[1].type == TokenType::LITERAL);
    REQUIRE(tokens[1].lexema == "hello world");
}

TEST_CASE("Reconhecendo strings") { 
    Lexer lexer("texto variavel = \"valor da variavel\" ");  
    vector<Token> tokens = lexer.inicializa();  
    REQUIRE(tokens[0].type == TokenType::TEXTO);
    REQUIRE(tokens[0].lexema == "texto");
}
