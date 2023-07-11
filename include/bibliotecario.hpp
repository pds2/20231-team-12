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
    /*
     * @brief Constrói um bibliotecário.
     * @param email Email do bibliotecário.
     * @param senha Senha do bibliotecário.
     */
    Bibliotecario(std::string, int);
    /*
     * @brief Destrói o bibliotecário.
     */
    ~Bibliotecario();

    /*
     * @brief Consulta a existência e os dados de um acervo pelo título.
     * @param titulo Título do acervo a ser buscado.
     */
    void consultar_acervo(std::string) override;
    /*
     * @brief Adiciona um acervo ao sistema.
     * @param codigo Codigo do acervo.
     * @param autor Autor do acervo.
     * @param titulo Título do sistema.
     * @param ano_publicacao Ano de publicação do acervo.
     * @param genero Gênero do acervo.
     */
    void adicionar_acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero);
    /*
     * @brief Adiciona um exemplar ao sistema.
     * @param codigo Código do acervo do exemplar.
     * @param codigoEspecifico Código do exemplar.
     * @param autor Autor do acervo.
     * @param titulo Título do acervo.
     * @param ano_publicacao Ano de publicação do acervo.
     * @param genero Gênero do acervo.
     */
    void adicionar_exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero);
    /*
     * @brief Remove um acervo do sistema.
     * @param codigo Codigo do acervo a ser removido.
     */
    void remover_acervo(int);   // remove acervo específico, pelo número CDU
    /*
     * @brief Remove um exemplar do sistema.
     * @param codigo Codigo do exemplar a ser removido.
     */
    void remover_exemplar(int); // remove do um dos exemplares de um acervo

    // std::vector consulta_geral_acervos(); // nao precisa ser um vector, mas vai ser uma lista de todos os livros
    // usar esse metodo pra deletar em massa? pessoa digita 1, 3, 4 etc e deleta ali os da lista

    /*
     * @brief Empresa um exemplar a um aluno.
     * @param livro Endereço do exemplar a ser emprestado.
     * @param aluno Aluno a receber o exemplar.
     */
    void emprestimo_de_exemplar(Exemplar *, Aluno &); // empresta um exemplar especifico a um aluno
    /*
     * @brief Faz a devolução de um livro de um aluno ao sistema.
     * @param codigo Código do exemplar a ser devolvido.
     * @param aluno Aluno a devolver o exemplar.
     */
    void devolucao_de_exemplar(int, Aluno &);  // retorna o exemplar à biblioteca
    /*
     * @brief Salva um bibliotecário no arquivo.
     */
    int salvar_bibl_no_arquivo();
};

#endif