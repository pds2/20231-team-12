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
    /*
     * @brief Constrói um exemplar.
     * @param codigo Código do acervo do exemplar.
     * @param codigoEspecífico Código do exemplar.
     * @param autor Autor do exemplar.
     * @param titulo Titulo do exemplar.
     * @param ano_publicacao Ano de publicação do exemplar.
     * @param genero Genero do exemplar.
     */
    Exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero);
    /*
     * @brief Destrói o exemplar.
     */
    ~Exemplar();
    /*
     * @brief Verifica se o exemplar está emprestado.
     */
    bool isEmprestado() const;
    /*
     * @brief Pega a data de empréstimo do exemplar.
     */
    int getDataEmprestimo() const;
    /*
     * @brief Pega o código do exemplar.
     */
    int getCodigoEspecifico() const;
    /*
     * @brief Pega a multa do exemplar.
     */
    double getMulta() const;

    /*
     * @brief Calcula a multa do exemplar.
     */
    int calculaMulta();
    /*
     * @brief Calcula a data de devolução do exemplar.
     */
    int calculaDataDevolucao();
    /*
     * @brief Salva o exemplar no arquivo.
     */
    int salva_exemplar_no_arquivo();

protected:
    void UpdateMultaExemplarAluno(const char* f, Exemplar* item);
    void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero); 
    bool checkTabelaExiste(const char*f, string nome_tabela);
    bool checkExemplar(const char* f, Exemplar* item);
    void bd_remover_exemplarespecifico(const char* f, Exemplar* item);
    void bd_destruir_tabela_exemplares(const char* f);
    void bd_acessar_tabela_exemplares(const char* f);
    void bd_inserir_tabela_exemplares(const char* f, Exemplar* item);
    void bd_criar_tabela_exemplares(const char* f);
    static void executar_sql(const char* f, string comandosql, string avisoerro);

};

#endif // EXEMPLAR_H
