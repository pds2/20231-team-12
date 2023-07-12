#include "../include/bibliotecario.hpp"

Bibliotecario::Bibliotecario(std::string email, int senha) : Perfil_usuario(email, senha)
{
    _papel = BIBLIOTECARIO;
    salvar_bibl_no_arquivo();
}

Bibliotecario::~Bibliotecario() {}

void Bibliotecario::consultar_acervo()
{
    std::ifstream arquivo_acervo("files/acervos.csv");
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
            getline(iss, genero, '\n'))
        {
            int codigo_int = std::stoi(codigo);
            int ano_publicacao_int = std::stoi(ano_publicacao);

            std::cout << "Acervo encontrado:\n";
            std::cout << "Código: " << codigo_int << '\n';
            std::cout << "Título: " << titulo_csv << '\n';
            std::cout << "Autor: " << autor << '\n';
            std::cout << "Ano de Publicação: " << ano_publicacao_int << '\n';
            std::cout << "Gênero: " << genero << '\n';
            std::cout << "-------------------\n";
        }
    }

    arquivo_acervo.close();
}

void Bibliotecario::consultar_acervo(std::string titulo) // pra bibliotecario retorna tudo sobre o acervo e quantidade de exemplares totais e emprestados
{
    std::ifstream arquivo_acervo("files/acervos.csv");
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

                std::cout << "Acervo encontrado:\n";
                std::cout << "Código: " << codigo_int << '\n';
                std::cout << "Título: " << titulo << '\n';
                std::cout << "Autor: " << autor << '\n';
                std::cout << "Ano de Publicação: " << ano_publicacao_int << '\n';
                std::cout << "Gênero: " << genero << '\n';
                std::cout << "-------------------\n";
            }
        }
    }

    arquivo_acervo.close();
}

void Bibliotecario::adicionar_acervo(Acervo &a)
{
    std::ofstream acervo_out;
    acervo_out.open("files/acervos.csv", std::ios_base::app);
    if (!acervo_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
    }
    else
    {
        acervo_out << a.get_codigo() << "," << a.get_autor() << "," << a.get_titulo() << ","
                   << a.get_ano_publicacao() << "," << a.get_genero() << std::endl;

        acervo_out.close();
    }
}

void Bibliotecario::adicionar_exemplar(Exemplar &e)
{
    std::ofstream exemplar_out;
    exemplar_out.open("files/exemplares.csv", std::ios_base::app);
    if (!exemplar_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
    }
    else
    {
        exemplar_out << e.get_codigo() << "," << e.getCodigoEspecifico() << "," << e.get_autor() << ","
                     << e.get_titulo() << "," << e.get_ano_publicacao() << "," << e.get_genero() << std::endl;

        exemplar_out.close();
    }
}

void Bibliotecario::remover_acervo(int codigo_acervo)
{

    std::ifstream arquivo_acervo("files/acervos.csv");
    std::ofstream arquivo_atualizado("files/acervos_temp.csv");
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

    remove("files/acervos.csv");
    rename("files/acervos_temp.csv", "files/acervos.csv");
}

void Bibliotecario::remover_exemplar(int codigo_exemplar)
{
    std::ifstream arquivo_acervo("files/exemplares.csv");
    std::ofstream arquivo_atualizado("files/exemplares_temp.csv");
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

    remove("files/exemplares.csv");
    rename("files/exemplares_temp.csv", "files/exemplares.csv");
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
    std::fstream bibli_file("files/usuarios.csv", std::ios_base::in | std::ios_base::out | std::ios_base::app);

    if (!bibli_file)
    {
        std::cout << "nao foi possivel abrir o arquivo" << std::endl;
        return 0;
    }

    std::string line;
    bool bibliotecarioExists = false;

    while (std::getline(bibli_file, line))
    {
        std::istringstream iss(line);
        std::string email;
        std::getline(iss, email, ',');
        if (email == this->get_email_perfil_usuario())
        {
            bibliotecarioExists = true;
            break;
        }
    }

    if (bibliotecarioExists)
    {
        std::cout << "bibliotecario ja existe" << std::endl;
        return 0;
    }
    else
    {
        bibli_file.clear();
        bibli_file.seekp(0, std::ios_base::end);
        bibli_file << this->get_ID_perfil_usuario() << ","
                   << this->get_email_perfil_usuario() << ","
                   << this->get_senha_perfil_usuario() << "," << this->get_papel_usuario() << "\n";
        bibli_file.close();
        return 1;
    }
}
