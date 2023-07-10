#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include <ctime>

#include "acervo.h"

class Exemplar : public Acervo
{
private:
    double multa;
    bool emprestado;
    int dataAquisicao;
    int dataEmprestimo;
    int codigoEspecifico;

public:
    Exemplar(std::string autor, int anoPublicacao, std::string titulo, int genero, float codigo,
             bool emprestado, int dataAquisicao, int codigoEspecifico);

    // Métodos getters
    bool isEmprestado() const;
    int getDataAquisicao() const;
    int getCodigoEspecifico() const;
    int getDataEmprestimo() const;
    double getMulta() const;

    // métodos
    int calculaMulta();
    int calculaDataDevolucao(); // isso vai servir pra calcular multa
    int salva_exemplar_no_arquivo();
};

#endif // EXEMPLAR_H
