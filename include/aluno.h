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
     * @brief Mostra todos os livros emprestados.
     */
    void get_livros_emprestados();
    /*
     * @brief Pega o numero de livros que o aluno possui.
     */
    int get_n_exemplares();

    // SO BIBLIOTECARIO PODE FAZER ISSO !!!!!!!!!!!!

    // nao acho que devolve um acervo, se bem que precisa

    Acervo consultar_acervo(Acervo) override;
    /*
     * @brief Consulta a multa de um livro pelo codigo.
     */
    void consultar_multa(Exemplar);
    /*
     * @brief Consulta a multa de todos os livros emprestados.
     */
    void consultar_multa_total(std::vector);

    int salvar_aluno_no_arquivo();
};

#endif