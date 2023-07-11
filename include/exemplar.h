#ifndef EXEMPLAR_H
#define EXEMPLAR_H

#include "acervo.h"


class Exemplar : public Acervo {

    private:
    bool emprestado;
    int dataEmprestimo;
    int codigoEspecifico;
    int multa;

public:

    /**
     * @brief Construtor da classe
     */
    Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, int codigo,
             bool emprestado, int codigoEspecifico);


    // Métodos getters
    /**
     * @brief Verifica se o exemplar está emprestado.
     */
    bool isEmprestado();

    /**
     * @brief Pega a data de empréstimo do exemplar.
     */
    int getdataEmprestimo() const;

    /**
     * @brief Obtém o código específico do exemplar.
     */
    int getCodigoEspecifico() const;

    /**
     * @brief Pega a data de devolução do exemplar.
     */
    int getDataDevolucao() const;

    /**
     * @brief Pega o valor da multa que foi calculado no calculaMulta
     */
    int getMulta();

    /**
     * @brief Define a data de empréstimo do exemplar.
     * //set -> Este set é necessário para realizar os test cases
     */
    //set
    void setDataEmprestimo(int dataEmprestimo);
    


    //métodos
    /**
     * @brief Calcula a data de devolução do exemplar, com base em 1 mês após a data de emprestimo
     */
    int calculaDataDevolucaoSistema(); 

    /**
     * @brief Calcula a multa do exemplar com base na data de devolução e nos dias passados apos a devolução estipulada no sistema
     */
    void calculaMulta();


    ~Exemplar();
    
    
};

#endif  // EXEMPLAR_H