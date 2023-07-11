#include <iostream>

#include "../include/bibliotecario.hpp"

int main()
{
    Bibliotecario bib1 = Bibliotecario("er", 123);

    std::cout << bib1.get_ID_perfil_usuario();
    return 0;
}