#include "../include/acervo.h"

Acervo::Acervo(std::string autor, int anoPublicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero, int codigo)
{
    _autor = autor;
    _ano_publicacao = anoPublicacao;
    _titulo = titulo;
    _genero = genero;
    _codigo = codigo;
}

std::string Acervo::get_autor()
{
    return _autor;
}

int Acervo::get_ano_publicacao()
{
    return _ano_publicacao;
}

std::string Acervo::get_titulo()
{
    return _titulo;
}

CODIGOS_GENEROS_ACERVO Acervo::get_genero()
{
    return _genero;
}

int Acervo::get_codigo()
{
    return _codigo;
}