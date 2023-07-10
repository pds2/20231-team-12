#ifndef PERFIL_USUARIO_H
#define PERFIL_USUARIO_H

#include <iostream>

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

    // só da pra criar um usuario com os 4 atributos juntos, nunca pode faltar um
    Perfil_usuario(std::string, int);

    unsigned int get_ID_perfil_usuario();
    std::string get_email_perfil_usuario();
    int get_senha_perfil_usuario();
    // essa é virtual pura, cada classe que herda vai declarar uma coisa diferente
    // nao pode criar um usuario sem papel
    virtual Papel_do_usuario set_papel_usuario() = 0;
    Papel_do_usuario get_papel_usuario();

    virtual Acervo consultar_acervo(Acervo) = 0;

    // destrutor
    ~Perfil_usuario();
};

#endif