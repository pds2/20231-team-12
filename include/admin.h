#ifndef ADMIN_H
#define ADMIN_H

#include <string>

#include "perfil_usuario.hpp"

class id_nao_existe_e {};
class id_invalido_e {};

class Admin : public Perfil_usuario {
    public:
        /*
         * Constroi um admin.
         */
        Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel);

        /*
         * @brief Deleta um aluno pelo id.
         */
        void deletar_aluno(unsigned int id);
        /*
         * @brief Deleta um bibliotecario pelo id.
         */
        void deletar_bibliotecario(unsigned int id);
        
        /*
         * Destroi o admin.
         */
        ~Admin();
};

#endif