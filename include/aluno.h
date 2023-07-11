#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <string>
#include <vector>

#include "exemplar.h"
#include "perfil_usuario.hpp"

class aluno_com_multa_e
{
};
class ja_possui_mutos_livros_e
{
};
class nao_possui_esse_livro_e
{
};

class Aluno : public Perfil_usuario
{
private:
    std::vector<Exemplar *> livros_com_aluno;

public:
    /*
     * @brief Constroi um aluno.
     */
    Aluno(std::string email, int senha);

    /*
     * @brief Mostra todos os livros emprestados ao aluno.
     */
    void get_livros_emprestados();
    /*
     * @brief Pega o numero de livros que o aluno possui.
     */
    int get_n_exemplares();

    // SO BIBLIOTECARIO PODE FAZER ISSO !!!!!!!!!!!!

    /*
     * @brief Empresta um livro ao aluno.
     */
    void emprestar_livro(Exemplar &livro);
    /*
     * @brief Devolve um livro do aluno.
     */
    void devolver_livro(int codigo);
    // nao acho que devolve um acervo, se bem que precisa
    void consultar_acervo(Acervo) override;
    /*
     * @brief Consulta a multa de um livro pelo codigo.
     */
    void consultar_multa(int);
    /*
     * @brief Consulta a multa de todos os livros emprestados.
     */
    void consultar_multa_total();

    void salvar_aluno_no_arquivo();
};

#endif