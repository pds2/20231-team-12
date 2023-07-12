#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <fstream>
#include <sstream>

//dedados.h"
#include "aluno.h"
#include "bibliotecario.hpp"

class email_invalido_e
{
};
class tipo_invalido_e
{
};

class Admin : public Perfil_usuario
{
protected:
    const char* file = "biblioteca.db";

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
    /* @brief Consulta o acervo (não é função do admin).
     */
    void consultar_acervo(std::string) override;
    /*
     * @brief Destroi o admin.
     */
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
    bool CheckAdmin(const char* f, Admin* adm);
};

#endif