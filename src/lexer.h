#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "token.h"

class Lexer {
private:
    std::string entrada;
    std::vector<Token> tokens;
    size_t posicao;
    int linha;
    int coluna;

    // Reserva prévia de espaço para vetores
    static const size_t RESERVA_INICIAL_TOKENS = 1000;

    // Mapas de palavras reservadas
    std::unordered_map<std::string, TokenType> palavrasReservadas;

    // Métodos auxiliares
    char proximoChar();
    void voltarChar();
    void ignorarEspacos();
    void ignorarComentarios();
    
    // Reconhecimento de tokens
    Token isStringLiteral();
    Token reconhecerNumero();
    Token reconhecerIdentificador();
    Token reconhecerString();
    Token reconhecerOperador();

    //debug
    void mostraTokens();
public:
    Lexer(const std::string& entrada);
    std::vector<Token> tokenizar();
    std::vector<Token> inicializa();
    // std::string inicializa();

    void imprimirTokens();

    // Tratamento de erros léxicos
    void reportarErro(const std::string& mensagem);
};

#endif // LEXER_H       