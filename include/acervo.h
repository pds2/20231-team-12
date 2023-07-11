#ifndef ACERVO_H
#define ACERVO_H

// #include "bancodedados.h"
#include <fstream>
#include <string>
#include <iostream>

// criar os codigos especificos de cada genero em um arquivo separado

// ACERVO NAO É virtual (pura), da pra criar um acervo sem ter nenhum exemplar (meio estranho mas ta certo)
class Acervo
{
private:
    int _codigo;
    std::string _autor;
    std::string _titulo;
    int _ano_publicacao;
    int _genero;

public:
    // Construtor
    Acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero);
    ~Acervo();
    bool operator<(const Acervo &acervo_custom) const;

    // getters
    std::string get_autor() const;
    int get_ano_publicacao() const;
    std::string get_titulo() const;
    int get_genero() const;
    int get_codigo() const;

    int salvar_acervo_no_arquivo();
};

#endif // ACERVO_H
