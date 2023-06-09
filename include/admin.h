#ifndef ADMIN_H
#define ADMIN_H

#include <string>

#include "perfil_usuario.hpp"

class Admin : public Perfil_usuario {
    public:
        /*
         * Constroi um admim.
         */
        Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel);
        /*
         * @brief Retorna o papel do Admin.
         */
        Papel_do_usuario get_papel_usuario() override;

        /*
         * @brief Deleta um usuario pelo id.
         */
        void deletar_usuario(unsigned int id);
        /*
         * @brief Deleta um bibliotecario pelo id.
         */
        void deletar_bibliotecario(unsigned int id);
};

#endif