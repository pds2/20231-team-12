#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <fstream>
#include <sstream>

//dedados.h"
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
protected:
    const char* file = "biblioteca.db";

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
     * @brief Destroi o admin.
     */
    virtual void consultar_acervo(std::string titulo) override;
    ~Admin();
protected:
    //Persistence.
    static void executar_sql(const char* f, string comandosql, string avisoerro);
    void bd_inserir_admin(const char* f, Admin* adm);
    void bd_inserir_aluno(const char* f, Aluno* aluno);
    void bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario);
    void bd_acessar_tabela_usuarios(const char* f);
    void bd_acessar_acervoportitulo(const char* f, std::string titulo);
    void bd_remover_usuario(const char* f, Perfil_usuario* user);
    void bd_remover_usuarioporid(const char* f, int id);
    void bd_remover_usuarioporemail(const char* f, string email);
    void bd_remover_aluno_e_devolver_exemplares(const char* f, Aluno *user);
    bool checkUsuario(const char* f, Perfil_usuario* user);
    bool checkTabelaExiste(const char*f, string nome_tabela);
    void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero);
    void UpdateMultaExemplarAluno(const char* f, Exemplar* item);
};

#endif