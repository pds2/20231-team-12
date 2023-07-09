#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include "acervo.h"


class Exemplar : public Acervo {
public:
    Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
             bool emprestado, int codigoEspecifico);

    // Métodos getters
    bool isEmprestado() const;
    int getdataEmprestimo() const;
    int getCodigoEspecifico() const;
    int getDataDevolucao() const;
    int getMulta() const;

    //set -> Necessário para realizar os test cases
    void setDataEmprestimo(int dataEmprestimo);

    //métodos
    
    void calculaMulta();
    int calculaDataDevolucaoSistema(); 


private:
    bool emprestado;
    int dataEmprestimo;
    int codigoEspecifico;
    int multa;
    //int dataDevolucaoUsuario;
    
};

#endif  // EXEMPLAR_H