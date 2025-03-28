#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Tipos de Dados
    NUMI,       // Número inteiro
    NUMF,       // Número ponto flutuante
    LETRA,      // Caractere
    TEXTO,      // String
    BOOLEANO,   // Valor booleano
    VAZIO,      // Tipo void

    // Palavras Reservadas
    SE,         // if
    SENAO,      // else
    SENAO_SE,   // else if
    ENQUANTO,   // while
    PARA,       // for
    FACA,       // do
    ESCOLHA,    // switch
    CASO,       // case
    PADRAO,     // default

    // Exceções
    TENTE,      // try
    ERRO,       // catch
    LANCAR,     // throw

    // Funções e Módulos
    FUNC,       // function
    RETORNA,    // return
    IMPORTA,    // include
    CLASSE,     // class
    PUBLICO,    // public
    PRIVADO,    // private

    // Operadores Lógicos
    E,          // and
    OU,         // or
    NAO,        // not

    // Operadores Matemáticos
    ADICAO,     // +
    SUBTRACAO,  // -
    MULTIPLICACAO, // *
    DIVISAO,    // /
    MODULO,     // %
    INCREMENTO, // ++
    DECREMENTO, // --

    // Operadores Comparação
    IGUAL,      // ==
    DIFERENTE,  // !=
    MAIOR,      // >
    MENOR,      // <
    MAIOR_IGUAL,// >=
    MENOR_IGUAL,// <=

    // Delimitadores
    PONTO_VIRGULA, // ;
    ABRE_CHAVE,    // {
    FECHA_CHAVE,   // }
    ABRE_COLCHETE, // [
    FECHA_COLCHETE,// ]
    ABRE_PARENTESE,// (
    FECHA_PARENTESE,// )
    ATRIBUICAO,    // =
    VIRGULA,       // ,
    PONTO,         // .
    SETA,          // ->

    // Entrada/Saída
    IMPRIMIR,      // print
    LER,           // input

    // Identificadores genéricos
    IDENTIFICADOR,
    FIM_ARQUIVO,
    DESCONHECIDO,
    LITERAL
};

struct Token {
    TokenType type;
    std::string lexema;
    int linha;
    int coluna;

    Token(TokenType type, const std::string& lexema, int linha, int coluna)
        : type(type), lexema(lexema), linha(linha), coluna(coluna) {}
};

// Função para converter TokenType para string
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::LITERAL: return "LITERAL";
        case TokenType::NUMI: return "NUMI";
        case TokenType::NUMF: return "NUMF";
        case TokenType::TEXTO: return "TEXTO";
        case TokenType::IMPRIMIR: return "IMPRIMIR";
        case TokenType::IDENTIFICADOR: return "IDENTIFICADOR";
        default: return "OUTRO";
    }
}

#endif // TOKEN_H