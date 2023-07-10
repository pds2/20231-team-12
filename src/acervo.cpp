#include "../include/acervo.h"

Acervo::Acervo(std::string autor, int ano_publicacao, std::string titulo,
               int genero, int codigo) : _autor(autor),
                                         _ano_publicacao(ano_publicacao),
                                         _titulo(titulo),
                                         _genero(genero),
                                         _codigo(codigo),
{
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

CODIGOS_GENEROS_ACERVO Acervo::get_genero() const
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
    acervo_out.open("acervos.csv", std::ios::in);
    if (!acervo_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        acervo_out >> this->_codigo >> this->_titulo >> this->_autor >> this->_ano_publicacao >> this->_genero;
        acervo_out.close();
        return 1;
    }
}