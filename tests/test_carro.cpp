#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "../include/doctest.h"
#include "../src/carro.hpp"
#include <sstream>

TEST_CASE("Testando o método exibirInfo") {
    std::ostringstream output;
    Carro carroTeste("Honda", 2020);
    
    carroTeste.exibirInfo(output);
    CHECK(carroTeste.get_marca() == "Honda");
    CHECK(output.str() == "Marca: dsa, Ano: 2020\n");
}