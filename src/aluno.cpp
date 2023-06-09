#include "../include/aluno.h"

#include <iostream>
#include <iomanip>

Aluno::Aluno(std::string email, int senha) : Perfil_usuario(email, senha)
{
    this->_papel = ALUNO;
    salvar_aluno_no_arquivo();
}

Aluno::~Aluno()
{
    for (auto it : livros_com_aluno)
    {
        delete it;
    }
    livros_com_aluno.clear();
}

/*
void Aluno::livros_emprestados()
{
    if (exemplares.size() == 0)
        std::cout << "O aluno nao possui nenhum livro." << std::endl;
    else
        std::cout << "Livro(s) emprestado(s) para o aluno:" << std::endl;
    for (auto l : exemplares)
        std::cout << l.getTitulo() << ", escrito por " << l.getAutor() << std::endl; // imprimir os dados dos livros
}
*/

void Aluno::get_livros_com_aluno()
{
    for (auto it : this->livros_com_aluno)
    {
        std::cout << std::endl
                  << it->get_titulo() << " ," << it->get_autor() << std::endl;
    }
    std::cout << "sem livros" << std::endl;
}

int Aluno::get_n_exemplares()
{
    return this->livros_com_aluno.size();
}

void Aluno::emprestar_livro(Exemplar *livro)
{
    if (this->livros_com_aluno.size() > 5)
        throw ja_possui_mutos_livros_e();
    for (auto l : livros_com_aluno)
    {
        livros_com_aluno.push_back(livro);
    }
}

void Aluno::devolver_livro(int codigo)
{
    bool p = true;
    for (auto l : this->livros_com_aluno)
        if (l->get_codigo() == codigo)
            p = false;
    if (p)
    {
        throw nao_possui_esse_livro_e();
    }

    int i = 0;
    for (auto l : livros_com_aluno)
    {
        if (l->get_codigo() == codigo)
            livros_com_aluno.erase(livros_com_aluno.begin() + i);
        i++;
    }
}

void Aluno::consultar_acervo(std::string titulo) // pro aluno so retorna codigo, titulo e autor, e # exemplares disponiveis
{
    std::ifstream arquivo_acervo("files/acervo.csv");
    if (!arquivo_acervo)
    {
        std::cout << "Falha ao abrir o arquivo" << std::endl;
        return;
    }

    std::string linha;
    while (getline(arquivo_acervo, linha))
    {
        std::istringstream iss(linha);
        std::string codigo, autor, titulo_csv, ano_publicacao, genero;

        if (getline(iss, codigo, ',') &&
            getline(iss, autor, ',') &&
            getline(iss, titulo_csv, ',') &&
            getline(iss, ano_publicacao, ',') &&
            getline(iss, genero, ','))
        {
            if (titulo_csv == titulo)
            {
                int codigo_int = std::stoi(codigo);

                std::cout << "Acervo encontrado:\n";
                std::cout << "Código: " << codigo_int << '\n';
                std::cout << "Título: " << titulo << '\n';
                std::cout << "Autor: " << autor << '\n';
            }
        }
    }

    arquivo_acervo.close();
}

/*
void Aluno::consultar_multa(int codigo)
{
    bool p = true;
    for (auto l : exemplares)
        if (l.getCodigoEspecifico() == codigo)
            p = false;
    if (p)
        throw nao_possui_esse_livro_e();
    double r;
    for (auto l : exemplares)
        if (l.getCodigoEspecifico() == codigo)
            r = l.calculaMulta();

    if (r == 0)
        std::cout << "Este livro não possui multa." << std::endl;
    else
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "A multa deste livro é de R$" << r << "." << std::endl;
    }
}



//SO ESSA AQUI
void Aluno::consultar_multa_total()
{
    double total = 0;
    std::cout << std::fixed << std::setprecision(2);
    for (auto l : this->livros_com_aluno)
    {
        double m = l->calculaMulta();
        total += m;
        if (m != 0)
            std::cout << "A multa de " << l->getTitulo() << " é de R$" << m << "." << std::endl;
    }
    if (total != 0)
        std::cout << "O total da(s) multa(s) de todos os livros é R$" << total << "." << std::endl;
    else
        std::cout << "Não há nenhuma multa no nome do aluno." << std::endl;
}
*/

int Aluno::salvar_aluno_no_arquivo()
{
    std::ofstream aluno_out;
    aluno_out.open("usuarios.csv", std::ios_base::app);
    if (!aluno_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        aluno_out << this->get_ID_perfil_usuario() << ","
                  << this->get_email_perfil_usuario() << "," << this->get_senha_perfil_usuario() << "," << this->get_senha_perfil_usuario() << std::endl;

        aluno_out.close();
        return 1;
    }
}
