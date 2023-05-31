#ifndef PERFIL_USUARIO_H
#define PERFIL_USUARIO_H

#include <iostream>

// TODOS os tipos de usuarios tem os mesmos atributos. o que muda sao os metodos que cada um pode fazer/tem acesso
// nao sei onde a gente usaria virtual e override, talvez para retornar livros visiveis para bibliotecarios mas ocultos pra alunos?
class Perfil_usuario
{
private:
    // esses 3 precisam estar relacionados no banco de dados
    unsigned int _ID_perfil_usuario;
    std::string _email_perfil_usuario;
    // senha só numeros, se for negativo lanca um erro
    int _senha_pefil_usuario;

public:
    // default, para testes
    Perfil_usuario();

    // só da pra criar um usuario com os 3 atributos juntos, nunca pode faltar um
    Perfil_usuario(unsigned int, std::string, int);

    unsigned int get_ID_perfil_usuario();
    std::string get_email_perfil_usuario();
    int get_senha_perfil_usuario();

    // destrutor
    ~Perfil_usuario();
};

#endif