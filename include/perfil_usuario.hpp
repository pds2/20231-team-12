#ifndef PERFIL_USUARIO_H
#define PERFIL_USUARIO_H

#include <iostream>

class Perfil
{
private:
    // esses 3 precisam estar relacionados no banco de dados
    unsigned int _ID_perfil_usuario;
    std::string _email_perfil_usuario;
};

#endif