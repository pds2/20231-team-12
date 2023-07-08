#ifndef PERFIL_BIBLIOTECARIO_H
#define PERFIL_BIBLIOTECARIO_H

#include <vector>

#include "exemplar.h"
#include "acervo.h"
#include "perfil_usuario.hpp"

class Bibliotecario : public Perfil_usuario
{
public:
    virtual Papel_do_usuario set_papel_usuario() override;

    // MUDAR OS TIPOS RECEBIDOS QUANDO A LAYLA FIZER OS ACERVOS

    void adicionar_acervo(Acervo); // adiciona um acervo preenchendo todos os campos
    // caso tenha um exemplar com o bibliotecario e ele queira adicionar, entra em adicionar_exemplar

    void adicionar_exemplar(Exemplar);

    void remover_acervo(Acervo); // remove acervo específico, pelo número CDU

    void remover_exemplar(Exemplar); // remove do um dos exemplares de um acervo

    // std::vector consulta_geral_acervos(); // nao precisa ser um vector, mas vai ser uma lista de todos os livros
    // usar esse metodo pra deletar em massa? pessoa digita 1, 3, 4 etc e deleta ali os da lista

    void emprestimo_de_exemplar(Exemplar); // empresta um exemplar especifico a um aluno

    void devolucao_de_exemplar(Exemplar); // retorna o exemplar à biblioteca
};

#endif