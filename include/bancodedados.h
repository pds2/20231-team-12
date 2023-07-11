#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include <string>

#include "../sqlite/sqlite3.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
#include "exemplar.h"
#include "aluno.h"
#include "admin.h"
#include "bibliotecario.hpp"

using namespace std;

class BD{
    public:

    /*        ESTA CLASSE EH APENAS UMA DOCUMENTACAO DOS METODOS DE PERSISTENCIA.     */

    /* const char* f eh referente ao arquivo .db que vai ser criado e/ou aberto.
    * por exemplo const char* file = "biblioteca.db";
    */

    ~BD() { };

    void executar_sql(const char* f, string comandosql, string avisoerro);

    //metodos que ciam as tabelas. funcionam da mesma forma. a repeticao eh necessaria.

    /*@brief cria a tabela acervos. */
    void bd_criar_tabela_acervos(const char* f);
    /*@brief cria a tabela usuarios. */
    void bd_criar_tabela_usuarios(const char* f);
    /*@brief cria a tabela exemplares. */
    void bd_criar_tabela_exemplares(const char* f);
    /*@brief cria uma tabela com os exemplares emprestados ao aluno com o id correspondente.*/
    void bd_criar_tabela_exemplaresaluno(const char* f);

    //metodos para destruir as tabelas.

    /*@brief destroi a tabela acervos. */
    void bd_destruir_tabela_acervos(const char* f);
    /*@brief destroi a tabela usuarios. */
    void bd_destruir_tabela_usuarios(const char* f);
    /*@brief destroi a tabela exemplares. */
    void bd_destruir_tabela_exemplares(const char* f);

    //metodos para inserir.

    /*@brief Insere acervos na tabela acervos se nao existe um acervo com o mesmo codigo. */
    void bd_inserir_tabela_acervos(const char* f, Acervo* livro);
    /*@brief (Auxiliar) Insere perfis na tabela usuarios se nao existe um perfil com o mesmo id. Papel eh indefinido.*/
    void bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user);
        /*@brief Add em Usuarios e faz um update de papel: indefinido para ADMIN.*/
        void bd_inserir_admin(const char* f, Admin* adm);
        /*@brief Add em Usuarios e faz um update de papel: indefinido para ALUNO.*/
        void bd_inserir_aluno(const char* f, Aluno* aluno);
        /*@brief Add em Usuarios e faz um update de papel: indefinido para BIBLIOTECARIO.*/
        void bd_inserir_bibliotecario(const char*f, Bibliotecario* bibliotecario);
    /*@brief Insere exemplares na tabela exemplares sem restricoes.*/
    void bd_inserir_tabela_exemplares(const char* f, Exemplar* item);
    /*@brief Insere os exemplares emprestados ao aluno com o id correspondente.*/
    void bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item);

    //metodos para acessar/selecionar.

    /*@brief Acessa e imprimi todos os dados na tabela acervos.*/
    void bd_acessar_tebela_acervos(const char* f);
    /*@brief Acessa e imprimi todos os dados na tabela usuarios.*/
    void bd_acessar_tabela_usuarios(const char* f);
    /*@brief Acessa e imprimi todos os dados na tabela exemplares.*/
    void bd_acessar_tabela_exemplares(const char* f);
    /*@brief Acessa e imprimi apenas os exemplares do aluno passado como parametro.*/
    void bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno);

    // metodos para remover.

    /* @brief remove um acervo e seus exemplares por seu codigo. */
    void bd_remover_acervo(const char* f, Acervo* livro);
    /* @brief remove um usuario por seu id. */
    void bd_remover_usuario(const char* f, Perfil_usuario* user);
    /*@brief remover por id.*/
    void bd_remover_usuarioporid(const char* f, int id);
    /*@brief remover por email.*/
    void bd_remover_usuarioporemail(const char* f, string email);
    /*@brief acessando um metodo auxiliar para remover exemplares e remover aluno.*/
    void bd_remover_aluno_e_devolver_exemplares(const char* f, Aluno* user);
    /* @brief remove um exemplar por seu codigo. */
    void bd_remover_exemplarespecifico(const char* f, Exemplar* item);
    /* @brief remove todos os exemplares associados ao acervo. */
    void bd_remover_exemplaresdoacervo(const char* f, Acervo* livro);
    /* @brief remove um exemplar em AlunoExemplares pelo codigo especifico do exemplar.*/
    void bd_remover_exemplaraluno(const char *f, int exemplarid);

    //metodos de checagem.

    /*@brief checa se ja existe um acervo com o mesmo codigo. TRUE p/EXISTE e FALSE p/NAO EXISTE*/
    bool checkAcervo(const char* f, Acervo* livro);

    /*@brief checa se ja existe um usuario com o mesmo id no bd. TRUE p/EXISTE e false p/NAO EXISTE*/
    bool checkUsuario(const char* f, Perfil_usuario* user);

    /*@brief verifica se o exemplar existe. True para EXISTE, False para NAO EXISTE. */
    bool checkExemplar(const char* f, Exemplar* item);

    /*@brief retorna o numero de exemplares de um acervo. */
    int checkNumExemplares(const char* f, Acervo* livro);

    /*@brief checa se a tabela existe. FALSE nao existe, TRUE existe.*/
    bool checkTabelaExiste(const char* f, string nome_tabela);

    //metodos update.
    /*@brief Atualiza se o livro esta emprestado(1) ou nãoemprestado/devolvido(0). */
    void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero);
    /*@brief Atualiza a multa referente a um exemplar.*/
    void UpdateMultaExemplarAluno(const char *f, Exemplar* item);

};

#endif