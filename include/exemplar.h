#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include <ctime>

#include "acervo.h"

class Exemplar : public Acervo
{
private:
    double multa;
    bool emprestado;
    int dataEmprestimo;
    int codigoEspecifico;

public:
    Exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero);
    ~Exemplar();
    // Métodos getters
    bool isEmprestado() const;
    int getDataEmprestimo() const;
    int getCodigoEspecifico() const;
    double getMulta() const;

    // métodos
    int calculaMulta();
    int calculaDataDevolucao(); // isso vai servir pra calcular multa
    int salva_exemplar_no_arquivo();
};

#endif // EXEMPLAR_H
