#include "../include/admin.h"

Admin::Admin(std::string email, int senha) : Perfil_usuario(email, senha)
{
    this->_papel = ADMIN;
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

    if(tipo_de_user != 0 && tipo_de_user !=2) throw tipo_invalido_e();

    if (tipo_de_user == ALUNO)

    {
        Aluno *novo_aluno = new Aluno(email, senha);
        novo_aluno->salvar_aluno_no_arquivo();
        delete novo_aluno;
    }

    else if (tipo_de_user == BIBLIOTECARIO)

    {
        Bibliotecario *novo_bibliotecario = new Bibliotecario(email, senha);
        novo_bibliotecario->salvar_bibl_no_arquivo();
        delete novo_bibliotecario;
    }
}

void Admin::deletar_usuario(std::string email)
{
    // verifica se o email não é do próprio admin
    if (this->get_email_perfil_usuario() == email)
    {
        throw email_invalido_e();
    }
    else
    {

        // bool b = true;
        //  for(todos os usuario do bd) if(usuario.get_ID_perfil_usuario()==id) b = false;
        // if (b)
        //    throw id_nao_existe_e();

        /*for(*todos os usuario do bd) {
            if(id do usuario == id) {
                if(usuario for aluno) devolver todos os livros que estão com o aluno
                deletar o usuario
            }
        }*/

        std::ifstream arquivo_usuarios("files/usuarios.csv");
        std::ofstream arquivo_atualizado("files/usuarios_temp.csv");
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

        remove("files/usuarios.csv");
        rename("files/usuarios_temp.csv", "files/usuarios.csv");
    }
}

void Admin::consultar_acervo(std::string)
{
    // nao pode acontecer nada aqui, admin nao liga pra livro
}

Admin::~Admin()
{
}
