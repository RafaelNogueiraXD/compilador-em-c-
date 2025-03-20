#!/bin/bash

if [ "$1" == "main" ]; then
    g++ -o output/main src/main.cpp && ./output/main
elif [ "$1" == "teste" ]; then
    g++ -std=c++17 -pthread -o output/testes tests/test_carro.cpp && ./output/testes
else
    echo "Uso: $0 [main|teste]"
    exit 1
fi
