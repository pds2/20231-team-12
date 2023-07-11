#include "../include/bibliotecario.hpp"

Bibliotecario::Bibliotecario(std::string email, int senha) : Perfil_usuario(email, senha)
{
    _papel = BIBLIOTECARIO;
    salvar_bibl_no_arquivo();
}

Bibliotecario::~Bibliotecario() {}

void Bibliotecario::consultar_acervo(std::string titulo) // pra bibliotecario retorna tudo sobre o acervo e quantidade de exemplares totais e emprestados
{
    std::ifstream arquivo_acervo("acervo.csv");
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
                int ano_publicacao_int = std::stoi(ano_publicacao);
                int genero_int = std::stoi(genero);

                std::cout << "Acervo encontrado:\n";
                std::cout << "Código: " << codigo_int << '\n';
                std::cout << "Título: " << titulo << '\n';
                std::cout << "Autor: " << autor << '\n';
                std::cout << "Ano de Publicação: " << ano_publicacao_int << '\n';
                std::cout << "Gênero: " << genero_int << '\n';
                std::cout << "-------------------\n";
            }
        }
    }

    arquivo_acervo.close();
}

void Bibliotecario::adicionar_acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero)
{
}

void Bibliotecario::adicionar_exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero)
{
    Exemplar novo_exemplar = Exemplar(codigo, codigoEspecifico, autor, titulo, ano_publicacao, genero);
}

void Bibliotecario::remover_acervo(int codigo_acervo)
{

    std::ifstream arquivo_acervo("acervos.csv");
    std::ofstream arquivo_atualizado("acervos_temp.csv");
    std::string linha;
    std::string codigo_string = std::to_string(codigo_acervo);

    //            int codigo = std::stoi(codigo_str);

    while (getline(arquivo_acervo, linha))
    {
        std::istringstream iss(linha);
        std::string campo;
        bool codigo_encontrado = false;

        while (getline(iss, campo, ','))
        {
            if (campo == codigo_string)
            {
                codigo_encontrado = true;
                break;
            }
        }

        if (!codigo_encontrado)
        {
            arquivo_atualizado << linha << '\n';
        }
    }

    arquivo_acervo.close();
    arquivo_atualizado.close();

    remove("acervos.csv");
    rename("acervos_temp.csv", "acervos.csv");
}

void Bibliotecario::remover_exemplar(int codigo_exemplar)
{
    std::ifstream arquivo_acervo("acervos.csv");
    std::ofstream arquivo_atualizado("acervos_temp.csv");
    std::string linha;
    std::string codigo_string = std::to_string(codigo_exemplar);

    //            int codigo = std::stoi(codigo_str);

    while (getline(arquivo_acervo, linha))
    {
        std::istringstream iss(linha);
        std::string campo;
        bool codigo_encontrado = false;

        while (getline(iss, campo, ','))
        {
            if (campo == codigo_string)
            {
                codigo_encontrado = true;
                break;
            }
        }

        if (!codigo_encontrado)
        {
            arquivo_atualizado << linha << '\n';
        }
    }

    arquivo_acervo.close();
    arquivo_atualizado.close();

    remove("acervos.csv");
    rename("acervos_temp.csv", "acervos.csv");
}

void Bibliotecario::emprestimo_de_exemplar(Exemplar *livro, Aluno &aluno)
{
    aluno.emprestar_livro(livro);
}

void Bibliotecario::devolucao_de_exemplar(int codigo, Aluno &aluno)
{
    aluno.devolver_livro(codigo);
}

int Bibliotecario::salvar_bibl_no_arquivo()
{
    std::ofstream bibli_out;
    bibli_out.open("usuarios.csv", std::ios_base::app);
    if (!bibli_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        bibli_out << this->get_ID_perfil_usuario() << ","
                  << this->get_email_perfil_usuario() << "," << this->get_senha_perfil_usuario() << "," << this->get_senha_perfil_usuario() << std::endl;
        bibli_out.close();
        return 1;
    }
}