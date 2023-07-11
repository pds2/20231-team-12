#include "../include/bibliotecario.hpp"

Bibliotecario::Bibliotecario(std::string email, int senha) : Perfil_usuario(email, senha)
{
    _papel = BIBLIOTECARIO;
}

void Bibliotecario::consultar_acervo(Acervo consulta)
{
}

void Bibliotecario::adicionar_acervo(Acervo acervo_novo)
{
}

void Bibliotecario::adicionar_exemplar(Exemplar exemplar_novo)
{
}

void Bibliotecario::remover_acervo(Acervo acervo_deletado)
{
}

void Bibliotecario::remover_exemplar(Exemplar exemplar_deletado)
{
}

void Bibliotecario::emprestimo_de_exemplar(Exemplar exemplar_emprestado)
{
}

void Bibliotecario::devolucao_de_exemplar(Exemplar exemplar_devolvido)
{
}

int Bibliotecario::salvar_bibl_no_arquivo()
{
    std::ofstream bibli_out;
    bibli_out.open("usuarios.csv", std::ios_base::app);
    if (!bibli_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        bibli_out << this->get_ID_perfil_usuario() << ","
                  << this->get_email_perfil_usuario() << "," << this->get_senha_perfil_usuario() << "," << this->get_senha_perfil_usuario() << std::endl;
        bibli_out.close();
        return 1;
    }
}