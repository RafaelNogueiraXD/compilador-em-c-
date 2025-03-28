#include "lexer.h"
#include "functions.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
Lexer::Lexer(const string& entrada) 
    : entrada(entrada), posicao(0), linha(1), coluna(1) {
    // cerr << "[DEBUG] Inicializando Lexer" << endl;
    palavrasReservadas = {
        {"letra", TokenType::LETRA},
        {"texto", TokenType::TEXTO},
        {"numi", TokenType::NUMI},
        {"numf", TokenType::NUMF},
        {"se", TokenType::SE},
        {"senao", TokenType::SENAO},
        {"enquanto", TokenType::ENQUANTO},
        {"para", TokenType::PARA},
        {"faca", TokenType::FACA},
        {"tente", TokenType::TENTE},
        {"erro", TokenType::ERRO},
        {"func", TokenType::FUNC},
        {"retorna", TokenType::RETORNA},
        {"importa", TokenType::IMPORTA},
        {"imprimir", TokenType::IMPRIMIR}
    };
}
char Lexer::proximoChar() {
    if (posicao >= entrada.length()) {
        return '\0';
    }
    char c = entrada[posicao++];
    
    if (c == '\n') {
        linha++;
        coluna = 1;
    } else {
        coluna++;
    }
    
    // cerr << "[DEBUG] proximoChar(): " << c << " (linha: " << linha << ", coluna: " << coluna << ")" << endl;
    return c;
}

Token Lexer::isStringLiteral(){
    int inicioLinha = linha;
    int inicioColuna = coluna - 1;
    
    // Extrair a string literal
    string stringLiteral = extractStringLiteral(entrada);
    
    // Calcular o tamanho da string literal
    int tamanhoString = stringLiteral.length();
    
    // Atualizar linha e coluna baseado no término da string
    for (char c : stringLiteral) {
        if (c == '\n') {
            linha++;
            coluna = 1;
        } else {
            coluna++;
        }
    }
    
    // Adicionar 2 para as aspas de início e fim
    coluna += 2;
    
    return Token(TokenType::LITERAL, stringLiteral, inicioLinha, inicioColuna);
}
std::vector<Token> Lexer::inicializa() {
    tokens.clear();
    posicao = 0;
    linha = 1;
    coluna = 1;

    ignorarEspacos(); // Ignorar espaços iniciais

    char c;
    while ((c = proximoChar()) != '\0') {
        if (isspace(c)) {
            cout << "Achei espaço em branco" << endl;
            ignorarEspacos();
            cout << "Posicao atual: " << posicao << endl;
            continue;
        }

        if (isalpha(c)) {
            cout << "Achei um identificador" << endl;
            tokens.push_back(reconhecerIdentificador());
            cout << "Posicao atual: " << posicao << endl;
            continue;
        }

        if (c == '"') {
            cout << "Achei uma literal string" << endl;
            tokens.push_back(isStringLiteral());
            cout << "Posicao atual: " << posicao << endl;
            continue;
        }
    }

    mostraTokens(); // Exibe os tokens
    return tokens;  // Retorna o vetor de tokens
}


void Lexer::voltarChar() {
    if (posicao > 0) {
        posicao--;
        if (posicao < entrada.length() && entrada[posicao] == '\n') {
            linha--;
            coluna = 1;
        } else if (coluna > 1) {
            coluna--;
        }
    }
}

Token Lexer::reconhecerIdentificador() {
    int inicioLinha = linha;
    int inicioColuna = coluna - 1;
    string identificador;

    char c = entrada[posicao - 1];
    while (isalnum(c) || c == '_') {
        identificador += c;
        c = proximoChar();
    }
    
    voltarChar();

    auto it = palavrasReservadas.find(identificador);
    if (it != palavrasReservadas.end()) {
        return Token(it->second, identificador, inicioLinha, inicioColuna);
    }

    // cerr << "[DEBUG] reconhecerIdentificador(): " << identificador << " (linha: " << inicioLinha << ", coluna: " << inicioColuna << ")" << endl;
    return Token(TokenType::IDENTIFICADOR, identificador, inicioLinha, inicioColuna);
}

void Lexer::ignorarEspacos() {
    while (posicao < entrada.length() && isspace(entrada[posicao])) {
        proximoChar();
    }
}




void Lexer::mostraTokens(){
    // Exibir cabeçalho
    std::cout << std::setw(15) << "Tipo"
                << std::setw(15) << "Lexema"
                << std::setw(10) << "Linha"
                << std::setw(10) << "Coluna" << "\n";
    std::cout << std::string(50, '-') << "\n";

    // Exibir cada token
    for (const auto& token : tokens) {
        std::cout << std::setw(15) << tokenTypeToString(token.type)
                    << std::setw(15) << token.lexema
                    << std::setw(10) << token.linha
                    << std::setw(10) << token.coluna << "\n";
    }
    
}