#ifndef ADMIN_H
#define ADMIN_H

#include <string>

#include "perfil_usuario.hpp"

class Admin : public Perfil_usuario {
    public:
        Admin(unsigned int id, std::string email, int senha);
        void deletar_usuario(unsigned int id);
        void deletar_bibliotecario(unsigned int id);
};

#endif