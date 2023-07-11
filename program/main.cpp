#include <iostream>

#include "../include/bibliotecario.hpp"

int main()
{
    Bibliotecario bib1 = Bibliotecario("er", 123);
    Bibliotecario bib2 = Bibliotecario("ee", 123);

    std::cout << "oi" << std::endl;
    std::cout << bib1.get_ID_perfil_usuario() << std::endl;
    std::cout << bib2.get_ID_perfil_usuario() << std::endl;
    return 0;
}
