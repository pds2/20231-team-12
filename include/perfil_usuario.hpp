#ifndef PERFIL_USUARIO_H
#define PERFIL_USUARIO_H

#include <iostream>
#include "acervo.h"
#include "exemplar.h"

// TODOS os tipos de usuarios tem os mesmos atributos. o que muda sao os metodos que cada um pode fazer/tem acesso
// nao sei onde a gente usaria virtual e override, talvez para retornar livros visiveis para bibliotecarios mas ocultos
// pra alunos?

enum Papel_do_usuario
{
    BIBLIOTECARIO,
    ADMIN,
    ALUNO
};

class Perfil_usuario
{
private:
    // esses 3 precisam estar relacionados no banco de dados
    static unsigned int CONTADOR_ID_perfil_usuario;
    unsigned int _ID_perfil_usuario;
    std::string _email_perfil_usuario;
    // senha só numeros, se for negativo lanca um erro
    int _senha_pefil_usuario;

protected:
    Papel_do_usuario _papel;

public:
    // default, para testes
    Perfil_usuario();

    /*
     * @brief Constroi um perfil do usuário.
     * @param string Email do usuário.
     * @param int senha do usuário.
     */
    Perfil_usuario(std::string, int);

    /*
     * @brief Pega o id do usuário.
     */
    unsigned int get_ID_perfil_usuario();
    /*
     * @brief Pega o email do usuário.
     */
    std::string get_email_perfil_usuario();
    /*
     * @brief Pega a senha do usuário.
     */
    int get_senha_perfil_usuario();
    /*
     * @brief Pega o papel do usuário.
     */
    Papel_do_usuario get_papel_usuario();
    /*
     * @brief Consulta um acervo (não definido para perfil_usuário).
     */
    virtual void consultar_acervo(std::string) = 0;

    /*
     * @brief Destrói o perfil do usuário.
     */
    ~Perfil_usuario();
};

#endif