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

    void emprestimo_de_exemplar(Exemplar *, Aluno &); // empresta um exemplar especifico a um aluno
    void devolucao_de_exemplar(int, Aluno &);         // retorna o exemplar à biblioteca

    int salvar_bibl_no_arquivo();
};

#endif