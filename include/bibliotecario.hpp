#ifndef PERFIL_BIBLIOTECARIO_H
#define PERFIL_BIBLIOTECARIO_H

#include <vector>

#include "exemplar.h"
#include "acervo.h"
#include "perfil_usuario.hpp"

class Bibliotecario : public Perfil_usuario
{
public:
    Bibliotecario(std::string, int);

    void consultar_acervo(Acervo) override;
    void adicionar_acervo(Acervo);
    void adicionar_exemplar(Exemplar);
    void remover_acervo(int);   // remove acervo específico, pelo número CDU
    void remover_exemplar(int); // remove do um dos exemplares de um acervo

    // std::vector consulta_geral_acervos(); // nao precisa ser um vector, mas vai ser uma lista de todos os livros
    // usar esse metodo pra deletar em massa? pessoa digita 1, 3, 4 etc e deleta ali os da lista

    void emprestimo_de_exemplar(int); // empresta um exemplar especifico a um aluno
    void devolucao_de_exemplar(int);  // retorna o exemplar à biblioteca

protected:
    //Persistence
    static void executar_sql(const char* f, string comandosql, string avisoerro);
    void bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario);
    void bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user);
    void bd_inserir_aluno(const char* f, Aluno* aluno);
    void bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item);
    void bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno);
    void bd_remover_exemplaraluno(const char *f, int exemplarid);
    bool checkUsuario(const char* f, Perfil_usuario* user);
    bool checkTabelaExiste(const char*f, string nome_tabela);
    void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero);
    void UpdateMultaExemplarAluno(const char* f, Exemplar* item);

};

#endif