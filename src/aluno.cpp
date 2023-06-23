#include "../include/aluno.h"

#include <iostream>

Aluno::Aluno(unsigned int id, std::string email, int senha): _n_livros(0), Perfil_usuario(id, email, senha) {
    std::cout << "Aluno criado!" << std::endl;
}

unsigned int Aluno::n_livros() {
    return _n_livros;
}

void Aluno::emprestar_livro() {
    _n_livros++;
}

/*
double consultar_multa(int n) {
    ...
}
*/