#include "aluno.h"

#include <iostream>
#include <iomanip>

Aluno::Aluno(std::string email, int senha) : Perfil_usuario(email, senha)
{
    _papel = ALUNO;
}

void Aluno::get_livros_emprestados()
{
    if (livros_com_aluno.size() == 0)
        std::cout << "O aluno nao possui nenhum livro." << std::endl;
    else
        std::cout << "Livro(s) emprestado(s) para o aluno:" << std::endl;
    for (auto l : livros_com_aluno)
        std::cout << l->get_titulo() << ", escrito por " << l->get_autor() << std::endl; // imprimir os dados dos livros
}

int Aluno::get_n_exemplares()
{
    return livros_com_aluno.size();
}

void Aluno::emprestar_livro(Exemplar &livro)
{
    if (livros_com_aluno.size() > 5)
        throw ja_possui_mutos_livros_e();
    for (auto l : livros_com_aluno)
        if (l->calculaMulta() != 0)
            throw aluno_com_multa_e();
    livros_com_aluno.push_back(&livro);
}

void Aluno::devolver_livro(int codigo)
{
    bool p = true;
    for (auto l : livros_com_aluno)
        if (l->getCodigoEspecifico() == codigo) p = false;
    if (p)
        throw nao_possui_esse_livro_e();

    for (auto it = livros_com_aluno.begin(); it != livros_com_aluno.end(); it++)
    {
        if ((*it)->getCodigoEspecifico() == codigo)
            livros_com_aluno.erase(it);
    }
}

Acervo Aluno::consultar_acervo(Acervo)
{
    //...
}

void Aluno::consultar_multa(Exemplar livro)
{
    bool p = true;
    for (auto l : livros_com_aluno)
        if (l->getCodigoEspecifico() == livro.getCodigoEspecifico())
            p = false;
    if (p)
        throw nao_possui_esse_livro_e();
    double r;
    for (auto l : livros_com_aluno)
        if (l->getCodigoEspecifico() == livro.getCodigoEspecifico())
            r = l->calculaMulta();

    if (r == 0)
        std::cout << "Este livro não possui multa." << std::endl;
    else
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "A multa deste livro é de R$" << r << "." << std::endl;
    }
}

void Aluno::consultar_multa_total()
{
    double total = 0;
    std::cout << std::fixed << std::setprecision(2);
    for (auto l : livros_com_aluno)
    {
        double m = l->calculaMulta();
        total += m;
        if (m != 0)
            std::cout << "A multa de " << l->get_titulo() << " é de R$" << m << "." << std::endl;
    }
    if (total != 0)
        std::cout << "O total da(s) multa(s) de todos os livros é R$" << total << "." << std::endl;
    else
        std::cout << "Não há nenhuma multa no nome do aluno." << std::endl;
}