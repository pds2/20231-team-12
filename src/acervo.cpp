#include "../include/acervo.h"

Acervo::Acervo(int codigo, std::string autor, std::string titulo,
               int ano_publicacao, std::string genero) : _codigo(codigo),
                                                 _autor(autor),
                                                 _titulo(titulo),
                                                 _ano_publicacao(ano_publicacao),
                                                 _genero(genero)
{
}

Acervo::~Acervo() {}

bool Acervo::operator<(const Acervo &acervo_custom) const
{
    if (acervo_custom.get_codigo() < this->_codigo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Acervo::get_autor() const
{
    return _autor;
}

int Acervo::get_ano_publicacao() const
{
    return _ano_publicacao;
}

std::string Acervo::get_titulo() const
{
    return _titulo;
}

std::string Acervo::get_genero() const
{
    return _genero;
}

int Acervo::get_codigo() const
{
    return _codigo;
}

int Acervo::salvar_acervo_no_arquivo()
{
    std::ofstream acervo_out;
    acervo_out.open("files/acervos.csv", std::ios_base::app);
    if (!acervo_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        acervo_out << this->_codigo << "," << this->_titulo << "," << this->_autor << "," << this->_ano_publicacao << "," << this->_genero;
        acervo_out.close();
        return 1;
    }
}
