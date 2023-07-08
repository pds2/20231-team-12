#include "aluno.h"

#include <iostream>
#include <iomanip>

Aluno::Aluno(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
}

Aluno::~Aluno() {
}

// void Aluno::livros_emprestados() {
//     if(exemplares.size()==0) std::cout << "O aluno nao possui nenhum livro." << std::endl;
//     else std::cout << "Livro(s) emprestado(s) para o aluno:" << std::endl;
//     for(auto l : exemplares) std::cout << l.getTitulo() << ", escrito por " << l.getAutor() << std::endl; // imprimir os dados dos livros
//     bibdados.bd_acessar_tabela_exemplaresaluno(file, *this);
// }

unsigned int Aluno::get_n_exemplares() {
    return exemplares.size();
}

// void Aluno::emprestar_livro(Exemplar livro) {
//     if(exemplares.size()>5) throw ja_possui_mutos_livros_e();
//     for(auto l : exemplares) if(l.calculaMulta()!=0) throw aluno_com_multa_e();
//     exemplares.push_back(livro);
//     bibdados.updateExemplarEmprestado(file, livro, 1);
//     bibdados.bd_inserir_alunoexemplar(file, &(*this), &livro);
// }

// void Aluno::devolver_livro(int codigo) {
//     bool p = true;
//     for(auto l : exemplares) if(l.getCodigoEspecifico()==codigo) p=false;
//     if(p) throw nao_possui_esse_livro_e();
    
//     //Persistence: esse for deve vir antes do for que contem erase.
//     for(Exemplar l : exemplares){
//         if(l.get_codigo_exemplar() == codigo){
//             bibdados.updateExemplarEmprestado(file, l, 0);
//             bibdados.bd_remover_exemplaraluno(file, codigo);
//         }
//     }
//     //

//     for(auto it = exemplares.begin(); it!=exemplares.end();it++) {
//         if(it->getCodigoEspecifico()==codigo) exemplares.erase(it);
//     }

// }

// void Aluno::consultar_acervo() {
//     bibdados.bd_acessar_tabela_exemplares(file);
// }

// void Aluno::consultar_multa(int codigo) {
//     bool p=true;
//     for(auto l:exemplares) if(l.getCodigoEspecifico()==codigo) p = false;
//     if(p) throw nao_possui_esse_livro_e();
//     double r;
//     for(auto l:exemplares) if(l.getCodigoEspecifico()==codigo) r=l.calculaMulta();
    
//     if(r==0) std::cout << "Este livro não possui multa." << std::endl;
//     else{
//         std::cout << std::fixed << std::setprecision(2);
//         std::cout << "A multa deste livro é de R$" << r << "." << std::endl;
//     }
// }

// void Aluno::consultar_multa_total() {
//     double total = 0;
//     std::cout << std::fixed << std::setprecision(2);
//     for(auto l : exemplares) {
//         double m = l.calculaMulta();
//         total+=m;
//         if(m!=0) std::cout << "A multa de " << l.getTitulo() << " é de R$" << m << "." << std::endl;
//     }
//     if(total!=0) std::cout << "O total da(s) multa(s) de todos os livros é R$" << total << "." << std::endl;
//     else std::cout << "Não há nenhuma multa no nome do aluno." << std::endl;
// }

//devolucao de todos os exemplares.
// void Aluno::BDauxiliar(string codigosecreto){
//     if(codigosecreto=="Persistence20231"){
//         for(Exemplar exemplaremprestado : exemplares){
//             bibdados.updateExemplarEmprestado(file, &exemplaremprestado, 0);
//             cout << "O Exemplar: "<< exemplaremprestado.get_codigo_exemplar() <<" foi devolvido."<<endl;
//         }
//     }
// }