#ifndef PERFIL_BIBLIOTECARIO_H
#define PERFIL_BIBLIOTECARIO_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "exemplar.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
#include "aluno.h"

class Bibliotecario : public Perfil_usuario
{
public:
    Bibliotecario(std::string, int);
    ~Bibliotecario();

    void consultar_acervo(std::string) override;
    void adicionar_acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero);
    void adicionar_exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero);
    void remover_acervo(int);   // remove acervo específico, pelo número CDU
    void remover_exemplar(int); // remove do um dos exemplares de um acervo

    // std::vector consulta_geral_acervos(); // nao precisa ser um vector, mas vai ser uma lista de todos os livros
    // usar esse metodo pra deletar em massa? pessoa digita 1, 3, 4 etc e deleta ali os da lista

    void emprestimo_de_exemplar(Exemplar *livro, Aluno &aluno); // empresta um exemplar especifico a um aluno
    void devolucao_de_exemplar(int, Aluno &);         // retorna o exemplar à biblioteca

    int salvar_bibl_no_arquivo();
    
protected:
    //Persistence
    static void executar_sql(const char* f, string comandosql, string avisoerro);
    void bd_criar_tabela_acervos(const char* f);
    void bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario);
    void bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user);
    void bd_criar_tabela_exemplares(const char* f);
    void bd_inserir_tabela_exemplares(const char* f, Exemplar* item);
    void bd_inserir_aluno(const char* f, Aluno* aluno);
    void bd_inserir_tabela_acervos(const char* f, Acervo* livro);
    void bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item);
    void bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno);
    void bd_remover_acervo(const char* f, Acervo *livro);
    void bd_remover_exemplarespecifico(const char* f, Exemplar* item);
    void bd_remover_exemplaraluno(const char *f, int exemplarid);
    void bd_remover_exemplaresdoacervo(const char* f, Acervo* livro);
    void bd_acessar_tabela_exemplares(const char* f);
    bool checkUsuario(const char* f, Perfil_usuario* user);
    bool checkAcervo(const char* f, Acervo* livro);
    bool checkExemplar(const char* f, Exemplar* item);
    bool checkExemplarAluno(const char* f, Exemplar* item);
    bool checkTabelaExiste(const char*f, string nome_tabela);
    void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero);
    void UpdateMultaExemplarAluno(const char* f, Exemplar* item);
};

#endif