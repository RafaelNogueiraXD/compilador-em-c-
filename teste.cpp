#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "doctest.h"

// Função a ser testada
int soma(int a, int b) {
    return a + b;
}

// Testes usando doctest
TEST_CASE("Testando a função soma") {
    CHECK(soma(2, 3) == 5);
    CHECK(soma(-1, 1) == 0);
    CHECK(soma(0, 0) == 0);
    CHECK(soma(10, -5) == 5);
}

// Outra função para teste
bool eh_par(int num) {
    return num % 2 == 0;
}

// Testes para a função eh_par
TEST_CASE("Testando a função eh_par") {
    CHECK(eh_par(2) == true);
    CHECK(eh_par(3) == false);
    CHECK(eh_par(0) == true);
    CHECK(eh_par(-4) == true);
}
