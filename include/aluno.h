#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <string>
#include <vector>

#include "exemplar.h"
#include "acervo.h"
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
    Aluno(std::string email, int senha);

    virtual ~Aluno();

    /*
     * @brief Mostra todos os livros emprestados.
     */
    void get_livros_com_aluno();
    /*
     * @brief Pega o numero de livros que o aluno possui.
     */
    int get_n_exemplares();

    void emprestar_livro(Exemplar *livro);
    // nao acho que devolve um acervo, se bem que precisa
    void devolver_livro(int codigo);

    void consultar_acervo(std::string) override;

    /*
     * @brief Consulta a multa de todos os livros emprestados.
     */
    // void consultar_multa_total();

    int salvar_aluno_no_arquivo();
};

#endif