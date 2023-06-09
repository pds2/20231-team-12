#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include "acervo.h"

class Exemplar : public Acervo {
public:
    Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
             bool emprestado, int dataAquisicao, int codigoEspecifico, int dataDevolucao);

    // Métodos getters
    bool isEmprestado() const;
    int getDataAquisicao() const;
    int getCodigoEspecifico() const;
    int getDataDevolucao() const;


private:
    bool emprestado;
    int dataAquisicao;
    int codigoEspecifico;
    int dataDevolucao;
};

#endif  // EXEMPLAR_H
