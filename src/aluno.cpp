#include "aluno.h"

#include <iostream>

Aluno::Aluno(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
    std::cout << "Aluno criado!" << std::endl;
}

Aluno::~Aluno() {
}

void Aluno::livros_emprestados() {
    if(exemplares.size()==0) std::cout << "O aluno nao possui nenhum livro." << std::endl;
    else std::cout << "Livro(s) emprestado(s) para o aluno:" << std::endl;
    for(auto l : exemplares) std::cout << l.getTitulo() << ", escrito por " << l.getAutor() << std::endl; // imprimir os dados dos livros
}

unsigned int Aluno::get_n_exemplares() {
    return exemplares.size();
}

void Aluno::emprestar_livro(Exemplar livro, int data) {
    if(exemplares.size()>5) throw ja_possui_mutos_livros_e();
    for(auto l : exemplares) if(l.calculaMulta(data)!=0) throw aluno_com_multa_e();
    exemplares.push_back(livro);
}

void Aluno::devolver_livro(int codigo) {
    if(exemplares.size()==0) throw nao_possui_esse_livro_e();
    bool p = true;
    for(auto l : exemplares) if(l.getCodigoEspecifico()==codigo) p=false;
    if(p) throw nao_possui_esse_livro_e();
    
    for(auto it = exemplares.begin(); it!=exemplares.end();it++) {
        if(it->getCodigoEspecifico()==codigo) exemplares.erase(it);
    }
}

void Aluno::consultar_acervo() {
    //...
}

double Aluno::consultar_multa(int codigo, int data) {
    bool p=true;
    for(auto l:exemplares) if(l.getCodigoEspecifico()==codigo) p = false;
    if(p) throw nao_possui_esse_livro_e();
    double r=0;
    for(auto l:exemplares) if(l.getCodigoEspecifico()==codigo) r=l.calculaMulta(data);
    return r;
}