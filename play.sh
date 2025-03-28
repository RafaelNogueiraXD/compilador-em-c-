#!/bin/bash
if [ "$1" == "main" ]; then
    g++ -o output/main src/main.cpp && ./output/main
fi
if [ "$1" == "teste" ]; then
    # g++ -std=c++17 -pthread -o output/test_token tests/test_token.cpp && ./output/test_token
    g++ -std=c++17 -pthread -o output/test_lexer tests/test_lexer.cpp && ./output/test_lexer
fi
