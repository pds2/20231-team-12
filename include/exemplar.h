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
