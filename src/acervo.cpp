#include "acervo.h"

Acervo::Acervo(std::string autor, int anoPublicacao, std::string titulo, std::string genero, std::string codigo)
    : autor(autor), anoPublicacao(anoPublicacao), titulo(titulo), genero(genero), codigo(codigo) {
}

Acervo::~Acervo() {
}

std::string Acervo::getAutor() const {
    return autor;
}

int Acervo::getAnoPublicacao() const {
    return anoPublicacao;
}

std::string Acervo::getTitulo() const {
    return titulo;
}

std::string Acervo::getGenero() const {
    return genero;
}

std::string Acervo::getCodigo() const {
    return codigo;
}