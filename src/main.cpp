#include <iostream>
#include <string>
#include "lexer.cpp"
using namespace std;
// bool isStringLiteral(const std::string& str) {
//     // Verifica se a string tem pelo menos 2 caracteres e se começa e termina com aspas
//     return str.length() >= 2 && str.front() == '"' && str.back() == '"';
// }

int main() {
    string input = "  \"outro teste\" e mais texto";
    Lexer analisador = Lexer(input);
    analisador.inicializa();
    // std::string var1 = "\"texto aleatorio\""; // String literal correta
    // std::string var2 = "texto aleatorio"; // Sem aspas
    
    // std::cout << "var1: " << (isStringLiteral(var1) ? "É uma string literal" : "Não é uma string literal") << std::endl;
    // std::cout << "var2: " << (isStringLiteral(var2) ? "É uma string literal" : "Não é uma string literal") << std::endl;
    
    return 0;
}
