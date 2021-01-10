#include <iostream>
#include "lexer.hpp"

int main(void) {
    int c = lexer::getToken();
    printf("%d", c);
    return 0;
}