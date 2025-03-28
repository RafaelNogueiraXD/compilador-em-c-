#include <iostream>
#include <string>
#include <algorithm>

std::string extractStringLiteral(const std::string& str) {
    // Remove espaços iniciais e finais
    size_t start = str.find('"');
    if (start == std::string::npos) return ""; // Não encontrou aspas
    
    size_t end = str.find('"', start + 1);
    if (end == std::string::npos) return ""; // Não encontrou a segunda aspa
    
    return str.substr(start + 1, end - start - 1);
}