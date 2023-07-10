#include "admin.h"

Admin::Admin(std::string email, int senha) : Perfil_usuario(email, senha)
{
    this->_papel = ADMIN;
    std::cout << "Admin criado." << std::endl;
}

void Admin::adicionar_usuario(int tipo_de_user, std::string email, int senha)
{
    /*
    if (papel == ADMIN)
        throw papel_invalido_e();

    Verifica se o email e id são novos ou já estão cadastrados com outro usuario. Se estiver,
    lançar alguma das exceções: email_ja_cadastrado_e e id_ja_cadastrado_e
    for(todos os usuarios do bd) {
        if(id==id do usuario) throw id_ja_cadastrado_e();
        if(email==email do usuario) throw email_ja_cadastrado_e();
    }

    if (papel == ALUNO)
    {
        Aluno a(id, email, senha, papel);
        // adiciona o aluno ao bd.
    }
    else
    {
        // Construtor ainda não definito
        // Bibliotecario b(id,email,senha,papel);
        // adiciona o bibliotecario ao bd.
    }
    */
}

void Admin::deletar_usuario(unsigned int id)
{
    // verifica se o id não é do próprio admin, e depois se existe algum usuario com esse id
    if (get_ID_perfil_usuario() == id)
        throw id_invalido_e();
    bool b = true;
    // for(*todos os usuario do bd*) if(usuario.get_ID_perfil_usuario()==id) b = false;
    if (b)
        throw id_nao_existe_e();

    /*for(*todos os usuario do bd*) {
        if(id do usuario == id) {
            if(usuario for aluno) devolver todos os livros que estão com o aluno
            deletar o usuario
        }
    }*/
}

Admin::~Admin() {}