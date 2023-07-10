#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <string>

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
     * Constroi um aluno.
     */
    Aluno(unsigned int id, std::string email, int senha);
    /*
     * Destroi o aluno.
     */
    ~Aluno();
    /*
     * @brief Mostra todos os livros emprestados.
     */
    std::vector get_livros_emprestados();
    /*
     * @brief Pega o numero de livros que o aluno possui.
     */
    int get_n_exemplares();

    // SO BIBLIOTECARIO PODE FAZER ISSO !!!!!!!!!!!!

    /*
     * @brief Empresta um livro ao aluno.
     */
    void emprestar_livro(Exemplar livro);
    /*
     * @brief Devolve um livro do aluno.
     */
    void devolver_livro(int codigo);
    /*
     * @brief Consulta os exemplares disponiveis.
     */

    // nao acho que devolve um acervo, se bem que precisa

    Acervo consultar_acervo(Acervo);
    /*
     * @brief Consulta a multa de um livro pelo codigo.
     */
    void consultar_multa(int codigo);
    /*
     * @brief Consulta a multa de todos os livros emprestados.
     */
    void consultar_multa_total();
};

#endif