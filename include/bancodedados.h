#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS

#include "../sqlite/sqlite3.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
#include "exemplar.h"

class BD{
    public:

    /* const char* f eh referente ao arquivo .db que vai ser criado e/ou aberto.
    * por exemplo const char* file = "biblioteca.db";
    */

    //metodos que ciam as tabelas. funcionam da mesma forma. a repeticao eh necessaria.

    /*@brief cria a tabela acervos. */
    void bd_criar_tabela_acervos(const char* f);

    /*@brief cria a tabela usuarios. */
    void bd_criar_tabela_usuarios(const char* f);

    /*@brief cria a tabela exemplares. */
    void bd_criar_tabela_exemplares(const char* f);

    //metodos para destruir as tabelas.

    /*@brief destroi a tabela acervos. */
    void bd_destruir_tabela_acervos(const char* f);

    /*@brief destroi a tabela usuarios. */
    void bd_destruir_tabela_usuarios(const char* f);

    /*@brief destroi a tabela exemplares. */
    void bd_destruir_tabela_exemplares(const char* f);

    //metodos para inserir.

    /*@brief Insere acervos na tabela acervos se nao existe um acervo com o mesmo codigo. */
    void bd_inserir_tabela_acervos(const char* f, Acervo livro);

    /*@brief Insere perfis na tabela usuarios se nao existe um perfil com o mesmo id. */
    void bd_inserir_tabela_usuarios(const char* f, Perfil_usuario user);

    /*@brief Insere exemplares na tabela exemplares sem restricoes.*/
    void bd_inserir_tabela_exemplares(const char* f, Exemplar item);

    //metodos para acessar/selecionar.

    /*@brief Acessa e imprimi todos os dados na tabela acervos.*/
    void bd_acessar_tebela_acervos(const char* f);

    /*@brief Acessa e imprimi todos os dados na tabela usuarios.*/
    void bd_acessar_tabela_usuarios(const char* f);

    /*@brief Acessa e imprimi todos os dados na tabela exemplares.*/
    void bd_acessar_tabela_exemplares(const char* f);

    // metodos para remover.

    /* @brief remove um acervo e seus exemplares por seu codigo. */
    void bd_remover_acervo(const char* f, Acervo livro);

    /* @brief remove um usuario por seu id. */
    void bd_remover_usuario(const char* f, Perfil_usuario user);

    /* @brief remove um exemplar por seu codigo. */
    void bd_remover_exemplar(const char* f, Exemplar item);

    //metodos de checagem.

    /*@brief checa se ja existe um acervo com o mesmo codigo e titulo. TRUE p/EXISTE e FALSE p/NAO EXISTE*/
    bool checkAcervo(const char* f, Acervo livro);

    /*@brief checa se ja existe um usuario com o mesmo id no bd. TRUE p/EXISTE e false p/NAO EXISTE*/
    bool checkUsuario(const char* f, Perfil_usuario user);

    /*@brief retorna o numero de exemplares de um acervo. */
    int checkNumExemplares(const char* f, Acervo livro);

    /*@brief checa se a tabela existe*/
    bool checkTabelaExiste(const char* f, string nome_tabela);

};

#endif