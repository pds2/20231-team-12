#include "admin.h"

Admin::Admin(std::string email, int senha) : Perfil_usuario(email, senha)
{
    this->_papel = ADMIN;
}

void Admin::adicionar_usuario(int tipo_de_user, std::string email, int senha)
{
    if (tipo_de_user = (int)ALUNO)
    {
        Aluno novo_aluno = Aluno(email, senha);
        novo_aluno.salvar_aluno_no_arquivo();
    }
    else if (tipo_de_user = (int)BIBLIOTECARIO)
    {
        Bibliotecario novo_bibliotecario = Bibliotecario(email, senha);
        novo_bibliotecario.salvar_bibl_no_arquivo();
    }
}

void Admin::deletar_usuario(std::string email)
{
    // verifica se o id não é do próprio admin, e depois se existe algum usuario com esse id
    if (this->get_email_perfil_usuario() == email)
    {
        throw id_invalido_e();
    }

    // bool b = true;
    //  for(*todos os usuario do bd*) if(usuario.get_ID_perfil_usuario()==id) b = false;
    // if (b)
    //    throw id_nao_existe_e();

    /*for(*todos os usuario do bd*) {
        if(id do usuario == id) {
            if(usuario for aluno) devolver todos os livros que estão com o aluno
            deletar o usuario
        }
    }*/

    std::ifstream arquivo_usuarios("usuarios.csv");
    std::ofstream arquivo_atualizado("usuarios_temp.csv");
    std::string linha;

    while (getline(arquivo_usuarios, linha))
    {
        std::istringstream iss(linha);
        std::string campo;
        bool email_encontrado = false;

        while (getline(iss, campo, ','))
        {
            if (campo == email)
            {
                email_encontrado = true;
                break;
            }
        }

        if (!email_encontrado)
        {
            arquivo_atualizado << linha << '\n';
        }
    }

    arquivo_usuarios.close();
    arquivo_atualizado.close();

    remove("usuarios.csv");
    rename("usuarios_temp.csv", "usuarios.csv");
}

void Admin::consultar_acervo(Acervo)
{
}

Admin::~Admin()
{
}