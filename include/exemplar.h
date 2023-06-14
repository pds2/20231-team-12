#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include <ctime>

#include "acervo.h"

// criar os tipos de codigo

class Exemplar : public Acervo
{
public:
    Exemplar(string autor, int anoPublicacao, string titulo, string genero, int codigo, int _codigo_exemplar);
    bool get_emprestado();
    time_t get_data;
    int get_codigo_exemplar();

private:
    bool _emprestado;
    time_t data;
    int _codigo_exemplar;
};

#endif