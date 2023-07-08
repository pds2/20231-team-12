#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <list>

#include "aluno.h"
#include "bibliotecario.hpp"

class email_ja_cadastrado_e
{
};
class id_invalido_e
{
};
class id_nao_existe_e
{
};
class id_ja_cadastrado_e
{
};
class papel_invalido_e
{
};

<<<<<<< HEAD
class Admin : public Perfil_usuario {
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

        //persistence
        /*@brief Imprimir todos os Usuarios.*/
        void consultar_Usuarios();

        void adicionar_usuario(Perfil_usuario* user);

        ~Admin();
=======
class Admin : public Perfil_usuario
{
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
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
};

#endif