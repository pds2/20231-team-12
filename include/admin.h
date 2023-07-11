#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <fstream>
#include <sstream>

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
     * @param email Email do admin.
     * @param senha Senha do admin.
     */
    Admin(std::string email, int senha);
    /*
     * @brief destroi o admin.
     */
    ~Admin();
    /*
     * @brief Cadastra um novo usuário no sistema.
     * @param tipo_de_user Tipo de usuário a inserir no sistema (0 para bibl.,2 para aluno).
     * @param email Email do usuário a inserir no sistema.
     * @param senha Senha do usuário a inserir no sistema.
     */
    void adicionar_usuario(int tipo_de_user, std::string email, int senha);
    /*
     * @brief Deleta um usuario pelo email.
     * @param email Email do usuário a ser deletado.
     */
    void deletar_usuario(std::string email);
    /*
     * @brief Consulta o acervo (não é função do admin).
     */
    void consultar_acervo(std::string) override;
};

#endif