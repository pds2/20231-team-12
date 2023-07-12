#ifndef ACERVO_H
#define ACERVO_H

// //dedados.h"
#include <fstream>
#include <string>
#include "../sqlite/sqlite3.h"
//dedados.h"
#include <iostream>

using namespace std;

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

protected:
    const char* file = "biblioteca.db";


public:
    /*
     * @brief Constroi um acervo.
     * @param codigo Código do acervo.
     * @param autor Autor do acervo.
     * @param titulo Título do acervo.
     * @param ano_publicacao Ano de publicação do acervo.
     * @param genero Gênero do acervo.
     */
    Acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero);
    /*
     * @brief Destrói o acervo.
     */
    ~Acervo();
    bool operator<(const Acervo &acervo_custom) const;

    /*
     * @brief Compara dois acervos com o operador <.
     */
    bool operator<(const Acervo &acervo_custom) const;
    /*
     * @brief Pega o autor do acervo.
     */
    std::string get_autor() const;
    /*
     * @brief Pega o ano de publicação do acervo.
     */
    int get_ano_publicacao() const;
    /*
     * @brief Pega o título do acervo.
     */
    std::string get_titulo() const;
    /*
     * @brief Pega o gênero do acervo.
     */
    int get_genero() const;
    /*
     * @brief Pega o código do acervo.
     */
    int get_codigo() const;
    /*
     * @brief Salva o acervo no arquivo.
     */
    int salvar_acervo_no_arquivo();

//persistence
protected:
    /* const char* f eh referente ao arquivo .db que vai ser criado e/ou aberto.
    * por exemplo const char* file = "biblioteca.db";
    */
    static void executar_sql(const char* f, string comandosql, string avisoerro);
    /*@brief cria a tabela acervos. */
    void bd_criar_tabela_acervos(const char* f);

    //metodos para destruir as tabelas.
    /*@brief destroi a tabela acervos. */
    void bd_destruir_tabela_acervos(const char* f);

    //metodos para inserir.
    /*@brief Insere acervos na tabela acervos se nao existe um acervo com o mesmo codigo. */
    void bd_inserir_tabela_acervos(const char* f, Acervo* livro);

    //metodos para acessar/selecionar.
    /*@brief Acessa e imprimi todos os dados na tabela acervos.*/
    void bd_acessar_tebela_acervos(const char* f);

    // metodos para remover.
    /* @brief remove um acervo e seus exemplares por seu codigo. */
    void bd_remover_acervo(const char* f, Acervo* livro);
    /* @brief remove um exemplar por seu codigo. */
    void bd_remover_exemplaresdoacervo(const char* f, Acervo* livro);

    //metodos de checagem.
    /*@brief checa se ja existe um acervo com o mesmo codigo. TRUE p/EXISTE e FALSE p/NAO EXISTE*/
    bool checkAcervo(const char* f, Acervo* livro);
    /*@brief retorna o numero de exemplares de um acervo. */
    int checkNumExemplares(const char* f, Acervo* livro);
    /*@brief checa se a tabela existe. FALSE nao existe, TRUE existe.*/
    bool checkTabelaExiste(const char* f, string nome_tabela);

};

#endif // ACERVO_H
