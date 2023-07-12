#include <iostream>

#include "../include/sistema.hpp"

int main()
{
    Sistema *sistema = new Sistema();
    sistema->inicia_sistema();

    delete sistema;
    return 0;
}
