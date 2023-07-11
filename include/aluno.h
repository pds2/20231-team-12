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
class ja_possui_esse_livro_e
{
};

class Aluno : public Perfil_usuario
{
private:
    std::vector<Exemplar *> livros_com_aluno;

public:
    /*
     * @brief Constrói um aluno.
     * @param email Email do aluno.
     * @param senha Senha do aluno.
     */
    Aluno(std::string email, int senha);
    /*
     * @brief Destrói o aluno.
     */
    ~Aluno();

    /*
     * @brief Pega todos os livros emprestados ao aluno.
     */
    std::vector<Exemplar *> get_livros_com_aluno();
    /*
     * @brief Pega o número de livros emprestados ao aluno.
     */
    int get_n_exemplares();
    /*
     * @brief Empresa um livro ao aluno.
     * @param livro Endereço do livro a ser emprestado.
     */
    void emprestar_livro(Exemplar *livro);
    /*
     * @brief Devolve um livro do aluno.
     * @param codigo Código do livro a ser emprestado.
     */
    void devolver_livro(int codigo);
    /*
     * @brief Consulta a existência de um acervo na biblioteca.
     * @param titulo Titulo do acervo a ser buscado.
     */
    void consultar_acervo(std::string titulo) override;
    /*
     * @brief Consulta a multa de todos os livros emprestados.
     */
    void consultar_multa_total();
    /*
     * @brief Salva o aluno no arquivo.
     */
    int salvar_aluno_no_arquivo();
};

#endif