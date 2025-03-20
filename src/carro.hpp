#include <iostream>
using namespace std;

class Carro {
private:
    string marca;
    int ano;

public:
    // Construtor
    Carro(string m, int a) {
        this->marca = m;
        ano = a;
    }
    string get_marca(){
        return this->marca;
    }
    // Método para exibir informações do carro
    void exibirInfo(ostream& out = cout) const {
        out << "Marca: " << marca << ", Ano: " << ano << std::endl;
    }
};
