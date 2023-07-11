#ifndef ADMIN_H
#define ADMIN_H

#include <string>

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

class Admin : public Perfil_usuario
{
public:
    /*
     * @brief Constroi um admin.
     */
    Admin(std::string email, int senha);
    /*
     * @brief Consulta o acervo.
     */
    Acervo consultar_acervo(Acervo) override;
    /*
     * @brief Cadastra um novo usuário no sistema.
     */
    void adicionar_usuario(int tipo_de_user, std::string email, int senha);
    /*
     * @brief Deleta um usuario por email.
     */
    void deletar_usuario(std::string email);
    /*
     * @brief Destroi o admin.
     */
    ~Admin();
};

#endif