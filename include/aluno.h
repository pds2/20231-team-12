#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <string>

#include "exemplar.h"
#include "perfil_usuario.hpp"

class aluno_com_multa_e {};
class ja_possui_mutos_livros_e {};
class nao_possui_esse_livro_e {};

class Aluno : public Perfil_usuario {
    private:
        std::list<Exemplar> exemplares;
        
    public:
        /*
         * Constroi um aluno.
         */
        Aluno(unsigned int id, std::string email, int senha, Papel_do_usuario papel);
        /*
         * Destroi o aluno.
         */
        ~Aluno();
        /*
         * @brief Mostra todos os livros emprestados.
         */
        void livros_emprestados();
        /*
         * @brief Pega o numero de livros que o aluno possui.
         */
        unsigned int get_n_exemplares();
        /*
         * @brief Empresta um livro ao aluno.
         */
        void emprestar_livro(Exemplar livro, int data);
        /*
         * @brief Devolve um livro do aluno.
         */
        void devolver_livro(int codigo);
         /*
         * @brief Consulta os exemplares disponiveis.
         */
        void consultar_acervo();
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