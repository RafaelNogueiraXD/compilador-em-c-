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
        {"imprimir", TokenType::IMPRIMIR},
        {"texto", TokenType::TEXTO}
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

void Lexer::ignorarEspacos() {
    while (posicao < entrada.length() && isspace(entrada[posicao])) {
        proximoChar();
    }
}

void Lexer::ignorarComentarios() {
    if (posicao + 1 < entrada.length() && entrada[posicao] == '/' && entrada[posicao + 1] == '/') {
        while (posicao < entrada.length() && entrada[posicao] != '\n') {
            posicao++;  // <- Aqui garantimos que a posição avança
        }
    }
}
Token Lexer::isStringLiteral(){
    int inicioLinha = linha;
    int inicioColuna = coluna - 1;
    return Token(TokenType::LITERAL,extractStringLiteral(entrada), inicioLinha, inicioColuna);

}
string Lexer::inicializa(){
    tokens.clear();
    posicao = 0;
    linha = 1;
    coluna = 1;
    if(proximoChar() == '"')
        cout << "achei uma literal string" << endl;
        tokens.push_back(isStringLiteral());
    mostraTokens();
    return "nada encontrado";
    // return tokens;
}
Token Lexer::reconhecerNumero() {
    int inicioLinha = linha;
    int inicioColuna = coluna - 1;
    string numero;
    bool ehPontoFlutuante = false;

    char c = entrada[posicao - 1];
    while (isdigit(c) || c == '.') {
        if (c == '.') {
            if (ehPontoFlutuante) {
                reportarErro("Número mal formado com múltiplos pontos.");
                break;
            }
            ehPontoFlutuante = true;
        }
        numero += c;
        c = proximoChar();
    }
    
    voltarChar();
    return Token(ehPontoFlutuante ? TokenType::NUMF : TokenType::NUMI, numero, inicioLinha, inicioColuna);
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

Token Lexer::reconhecerOperador() {
    int inicioLinha = linha;
    int inicioColuna = coluna - 1;
    char c = entrada[posicao - 1];

    unordered_map<string, TokenType> operadores = {
        {"+", TokenType::ADICAO},
        {"-", TokenType::SUBTRACAO},
        {"*", TokenType::MULTIPLICACAO},
        {"/", TokenType::DIVISAO},
        {"==", TokenType::IGUAL},
        {"!=", TokenType::DIFERENTE},
        {"++", TokenType::INCREMENTO},
        {"--", TokenType::DECREMENTO}
    };
    if (posicao + 1 < entrada.length()) {
        char proximoC = entrada[posicao];
    }

    // if (posicao < entrada.length()) {
        // char proximoC = entrada[posicao];
        // string doisCaracteres = {c, proximoC};

        // if (operadores.count(doisCaracteres)) {
        //     proximoChar();
        //     return Token(operadores[doisCaracteres], doisCaracteres, inicioLinha, inicioColuna);
        // }
    // }

    if (operadores.count(string(1, c))) {
        return Token(operadores[string(1, c)], string(1, c), inicioLinha, inicioColuna);
    }

    return Token(TokenType::DESCONHECIDO, string(1, c), inicioLinha, inicioColuna);
}
vector<Token> Lexer::tokenizar() {
    tokens.clear();
    posicao = 0;
    linha = 1;
    coluna = 1;

    while (posicao < entrada.length()) {
        ignorarEspacos();
        ignorarComentarios();

        if (posicao >= entrada.length()) break;

        char c = proximoChar();
        
        // cerr << "[DEBUG] tokenizar(): analisando '" << c << "' na linha " << linha << " coluna " << coluna << endl;
        
        if (isdigit(c)) {
            voltarChar();
            tokens.push_back(reconhecerNumero());
        }
        else if (isalpha(c) || c == '_') {
            voltarChar();
            tokens.push_back(reconhecerIdentificador());
        }
        else if (ispunct(c)) {
            voltarChar();
            tokens.push_back(reconhecerOperador());
        }
        else {
            reportarErro("Caractere não reconhecido: " + string(1, c));
            posicao++;
        }
    }

    tokens.push_back(Token(TokenType::FIM_ARQUIVO, "", linha, coluna));
    return tokens;
}

void Lexer::imprimirTokens() {
    for (const auto& token : tokens) {
        cout << "Token: " << token.lexema 
                  << " (Linha: " << token.linha 
                  << ", Coluna: " << token.coluna << ")" << endl;
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


void Lexer::reportarErro(const string& mensagem) {
    throw runtime_error("Erro Léxico: " + mensagem + " na linha " + to_string(linha) + ", coluna " + to_string(coluna));
}