#include "../include/acervo.h"

<<<<<<< HEAD
Acervo::Acervo(std::string autor, int ano_publicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero, int codigo)
{
    _autor = autor;
    _ano_publicacao = ano_publicacao;
    _titulo = titulo;
    _genero = genero;
    _codigo = codigo;
}

std::string Acervo::get_autor()
=======
Acervo::Acervo(std::string autor, int ano_publicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero, int codigo) : _autor(autor),
                                                                                                                       _ano_publicacao(ano_publicacao), _titulo(titulo), _genero(genero), _codigo(codigo)
{
}

std::string Acervo::get_autor() const
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
{
    return _autor;
}

<<<<<<< HEAD
int Acervo::get_ano_publicacao()
=======
int Acervo::get_ano_publicacao() const
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
{
    return _ano_publicacao;
}

<<<<<<< HEAD
std::string Acervo::get_titulo()
=======
std::string Acervo::get_titulo() const
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
{
    return _titulo;
}

<<<<<<< HEAD
CODIGOS_GENEROS_ACERVO Acervo::get_genero()
=======
CODIGOS_GENEROS_ACERVO Acervo::get_genero() const
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
{
    return _genero;
}

<<<<<<< HEAD
int Acervo::get_codigo()
=======
int Acervo::get_codigo() const
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
{
    return _codigo;
}