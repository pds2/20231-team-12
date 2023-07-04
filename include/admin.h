#ifndef ADMIN_H
#define ADMIN_H

#include <string>

<<<<<<< HEAD
#include "aluno.h"
#include "bibliotecario.hpp"

class email_ja_cadastrado_e {};
class id_invalido_e {};
class id_nao_existe_e {};
class id_ja_cadastrado_e {};
class papel_invalido_e {};

class Admin : public Perfil_usuario {
    private:
        const char* file = "biblioteca.db";
        BD bibdados;
    public:
        /*
         * Constroi um admin.
         */
        Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel);
        /*
         * @brief Cadastra um novo usuário no sistema.
         */
        void adicionar_usuario(unsigned int id, std::string email, int senha, Papel_do_usuario papel);
        /*
         * @brief Deleta um usuario pelo id.
         */
        void deletar_usuario(unsigned int id);
        /*
         * Destroi o admin.
         */
        ~Admin();
=======
#include "perfil_usuario.hpp"

class Admin : public Perfil_usuario {
    public:
        Admin(unsigned int id, std::string email, int senha);
        void deletar_usuario(unsigned int id);
        void deletar_bibliotecario(unsigned int id);
>>>>>>> c08a5ddf6fdc1e401968fd7bbcf64b6c10236287
};

#endif