#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include <ctime>

#include "acervo.h"

// criar os tipos de codigo
enum CODIGOS_SUBGENEROS_EXEMPLARES
{
    MATEMATICA_BASICA,
    CALCULO_1,
    CALCULO_2
};

class Exemplar : public Acervo
{
private:
    bool _emprestado;
    time_t dia_emprestado;
    CODIGOS_SUBGENEROS_EXEMPLARES _codigo_exemplar;

public:
    Exemplar(std::string autor, int anoPublicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero, int codigo, CODIGOS_SUBGENEROS_EXEMPLARES _codigo_exemplar);
    bool get_emprestado();
    time_t get_dia_emprestado;
    int get_codigo_exemplar();
};

#endif