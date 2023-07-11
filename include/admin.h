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
     * Constroi um admin.
     */
    Admin(std::string email, int senha);
    /*
     * @brief Cadastra um novo usuário no sistema.
     */
    void adicionar_usuario(int tipo_de_user, std::string email, int senha);
    /*
     * @brief Deleta um usuario pelo id.
     */
    void deletar_usuario(std::string email);
    /*
     * Destroi o admin.
     */
    virtual void consultar_acervo(std::string) override;
    ~Admin();
};

#endif