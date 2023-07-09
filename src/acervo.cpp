#include "../include/acervo.h"

BD bibdados;

Acervo::Acervo(std::string autor, int ano_publicacao, std::string titulo, std::string genero, int codigo) 
{
    _autor= autor;
    _ano_publicacao = ano_publicacao;
    _titulo = titulo;
    _genero = genero;
    _codigo = codigo;

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