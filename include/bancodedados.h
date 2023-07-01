#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS

#include "../sqlite/sqlite3.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
#include "exemplar.h"

class BD{
    public:

    /* const char* f eh referenta ao arquivo .db que sera criado e/ou aberto.
    por exemplo const char* file = "biblioteca.db";
    */

    //metodos que ciam as tabelas. funcionam da mesma forma. a repeticao eh necessaria.
    static void bd_criar_tabela_acervos(const char* f);
    static void bd_criar_tabela_usuarios(const char* f);
    static void bd_criar_tabela_exemplares(const char* f);

    //metodos para destruir as tabelas.
    static void bd_destruir_tabela_acervos(const char* f);
    static void bd_destruir_tabela_usuarios(const char* f);
    static void bd_destruir_tabela_exemplares(const char* f);

    //metodos para inserir.
    static void bd_inserir_tabela_acervos(const char* f, Acervo livro);
    static void bd_inserir_tabela_usuarios(const char* f, Perfil_usuario user);
    static void bd_inserir_tabela_exemplares(const char* f, Exemplar item);

    //metodos para acessar/selecionar.
    static void bd_acessar_tebela_acervos(const char* f);
    static void bd_acessar_tabela_usuarios(const char* f);
    static void bd_acessar_tabela_exemplares(const char* f);

    // metodos para remover.
    
    /* @brief remove um acervo por seu codigo. */
    static void bd_remover_acervo(const char* f, Acervo livro);
    /* @brief remove um usuario por seu id. */
    static void bd_remover_usuario(const char* f, Perfil_usuario user);
    /* @brief remove um exemplar por seu codigo. */
    static void bd_remover_exemplar(const char* f, Exemplar item);

};

#endif