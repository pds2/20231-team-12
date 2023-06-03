#ifndef ALUNO_H
#define ALUNO_H

#include <string>

#include "perfil_usuario.hpp"

class Aluno : public Perfil_usuario {
    private:
        //só uma variável que eu pensei que talvez o aluno teria, ex: cada um pode ter
        //no max x livros, se já tiver x não pode ter mais
        unsigned int _n_livros;
    public:
        Aluno(unsigned int id, std::string email, int senha);
        unsigned int n_livros();
        void emprestar_livro();
        //double consultar_multa(int codigo);
};

#endif