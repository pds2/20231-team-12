#ifndef PERFIL_BIBLIOTECARIO_H
#define PERFIL_BIBLIOTECARIO_H

#include <vector>
#include <string>

#include "exemplar.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
#include "bancodedados.h"

class Bibliotecario : public Perfil_usuario
{
    
public:
    Bibliotecario(std::string, int);

    Acervo consultar_acervo(Acervo) override;
    void adicionar_acervo(Acervo);
    void adicionar_exemplar(Exemplar);
    void remover_acervo(int);   // remove acervo específico, pelo número CDU
    void remover_exemplar(int); // remove do um dos exemplares de um acervo

    void consulta_geral_acervos(Exemplar); // nao precisa ser um vector, mas vai ser uma lista de todos os livros
    // usar esse metodo pra deletar em massa? pessoa digita 1, 3, 4 etc e deleta ali os da lista
    // integrar com o bd

    void emprestimo_de_exemplar(int); // empresta um exemplar especifico a um aluno
    void devolucao_de_exemplar(int);  // retorna o exemplar à biblioteca
};

#endif