#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <string>

#include "exemplar.h"
#include "perfil_usuario.hpp"

class Aluno : public Perfil_usuario {
    private:
        std::list<Exemplar> exemplares;
        
    public:
        /*
         * Constroi um aluno.
         */
        Aluno(unsigned int id, std::string email, int senha, Papel_do_usuario papel);
        /*
         * @brief Retorna o papel do Aluno.
         */
        Papel_do_usuario get_papel_usuario() override;
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
        void emprestar_livro(Exemplar livro);
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
        double consultar_multa(int codigo);
};

#endif