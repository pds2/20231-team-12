#include "aluno.h"

#include <iostream>

Aluno::Aluno(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
    std::cout << "Aluno criado!" << std::endl;
}
Papel_do_usuario Aluno::get_papel_usuario() {
    return ALUNO;
}
void Aluno::livros_emprestados() {
    for(auto l : exemplares) std::cout << 0; // imprimir os dados dos livros
}

unsigned int Aluno::get_n_exemplares() {
    return exemplares.size();
}

void Aluno::emprestar_livro(Exemplar livro) {
    exemplares.push_back(livro);
}

void Aluno::devolver_livro(int codigo) {
    for(auto it = exemplares.begin(); it!=exemplares.end();it++) {
        if(it->get_codigo()==codigo) exemplares.erase(it);
    }
}

void Aluno::consultar_acervo() {
    //...
}

double Aluno::consultar_multa(int n) {
    //...
    return 0;
}