#include "../include/sistema.hpp"

Sistema::Sistema()
{
    // abre arquivo users, pega todos os users e deixa no ram
    // abre arquivo acervos, abre arquivo exemplares
    // pega acervos, PROCURA NO ARQUIVO INTEIRO se ele tem algum exemplar
    // tem: cadastra ele (se nao tiver exemplar continua um vetor vazio)
    // FEITO
    carregar_acervos();
    carregar_usuarios();
}

//    Acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero);

// Load exemplares from "exemplares.csv"
/*
void Sistema::carregar_exemplares()
{
    std::ifstream arquivo_exemplares("exemplares.csv");
    if (!arquivo_exemplares)
    {
        std::cout << "Falha ao abrir o arquivo exemplares.csv" << std::endl;
    }

    std::string linha;
    while (getline(arquivo_exemplares, linha))
    {
        std::istringstream iss(linha);
        std::string campo;

        // Parse exemplar fields
        std::string autor, titulo, ano_publicacao_str, genero_str, codigo_str, codigo_esp_string;
        if (getline(iss, codigo_str, ',') &&
            getline(iss, codigo_esp_string, ',') &&
            getline(iss, autor, ',') &&
            getline(iss, titulo, ',') &&
            getline(iss, ano_publicacao_str, ',') &&
            getline(iss, genero_str, ','))
        {
            int ano_publicacao = std::stoi(ano_publicacao_str);
            int genero = std::stoi(genero_str);
            int codigo = std::stoi(codigo_str);
            int codigo_especifico = std::stoi(codigo_esp_string);

            // Create an Exemplar object
            Exemplar exemplar = Exemplar(codigo, codigo_especifico, autor, titulo, ano_publicacao, genero);

            // Add the Exemplar to the biblioteca map
            Acervo acervo(codigo, autor, titulo, ano_publicacao, genero);
            biblioteca[acervo].push_back(exemplar);
        }
    }

    arquivo_exemplares.close();
}
*/

// Load acervos from "acervos.csv"

// ESSE CODIGO NAO É EFICIENTE
void Sistema::carregar_acervos()
{

    // carrega os dois arquivos
    std::ifstream arquivo_acervos("acervos.csv");
    if (!arquivo_acervos)
    {
        std::cout << "Falha ao abrir o arquivo acervos.csv" << std::endl;
        std::__throw_bad_exception(); // trocar isso por um erro de verdade pessoal
    }
    std::ifstream arquivo_exemplares("exemplares.csv");
    if (!arquivo_exemplares)
    {
        std::cout << "Falha ao abrir o arquivo exemplares.csv" << std::endl;
        std::__throw_bad_exception();
    }

    // pra cada linha de acervo
    std::string linha_acervo;
    std::string linha_exemplar;
    while (getline(arquivo_acervos, linha_acervo))
    {
        std::istringstream iss(linha_acervo);
        std::string campo_acervo;

        // Parse acervo fields
        std::string autor, titulo, ano_publicacao_str, genero_str, codigo_acervo_str;
        if (getline(iss, autor, ',') &&
            getline(iss, titulo, ',') &&
            getline(iss, ano_publicacao_str, ',') &&
            getline(iss, genero_str, ',') &&
            getline(iss, codigo_acervo_str, '\n'))
        {
            int ano_publicacao = std::stoi(ano_publicacao_str);
            int genero = std::stoi(genero_str);
            int codigo_acervo = std::stoi(codigo_acervo_str);

            // Create an Acervo object
            Acervo acervo(codigo_acervo, autor, titulo, ano_publicacao, genero);

            // Add the Acervo to the biblioteca map if it doesn't exist
            if (biblioteca.count(acervo) == 0)
            {
                biblioteca.emplace(acervo, std::vector<Exemplar>());
            }

            // pra cada linha de exemplar
            while (getline(arquivo_exemplares, linha_exemplar))
            {
                std::istringstream iss(linha_exemplar);
                std::string campo_exemplar;

                // Parse acervo fields
                std::string autor, titulo, ano_publicacao_str, genero_str, codigo_exemplar_str, codigo_esp_string;
                if (getline(iss, codigo_exemplar_str, ',') &&
                    getline(iss, codigo_esp_string, ',') &&
                    getline(iss, autor, ',') &&
                    getline(iss, titulo, ',') &&
                    getline(iss, ano_publicacao_str, ',') &&
                    getline(iss, genero_str, '\n'))
                {
                    int ano_publicacao = std::stoi(ano_publicacao_str);
                    int genero = std::stoi(genero_str);
                    int codigo_exemplar = std::stoi(codigo_exemplar_str);
                    int codigo_especifico = std::stoi(codigo_esp_string);

                    Exemplar exemplar = Exemplar(codigo_exemplar, codigo_especifico, autor, titulo, ano_publicacao, genero);
                    if (codigo_acervo == codigo_exemplar)
                    {
                        ;
                    }
                }
            }
        }

        arquivo_acervos.close();
        arquivo_exemplares.close();
    }
}

// Load usuarios from "usuarios.csv"
void Sistema::carregar_usuarios()
{
    std::ifstream arquivo_usuarios("usuarios.csv");
    if (!arquivo_usuarios)
    {
        std::cout << "Falha ao abrir o arquivo usuarios.csv" << std::endl;
        return;
    }

    std::string linha;
    while (getline(arquivo_usuarios, linha))
    {
        std::istringstream iss(linha);
        std::string campo;

        // Parse usuario fields
        std::string tipo_usuario, email, senha_str, ID_udusario;
        if (getline(iss, tipo_usuario, ',') &&
            getline(iss, email, ',') &&
            getline(iss, senha_str, ',') &&
            getline(iss, ID_udusario, ','))
        {
            int senha = std::stoi(senha_str);
            // Create a Perfil_usuario object
            Perfil_usuario *perfil_usuario = nullptr;
            if (tipo_usuario == "Aluno")
            {
                perfil_usuario = new Aluno(email, senha);
            }
            else if (tipo_usuario == "Bibliotecario")
            {
                perfil_usuario = new Bibliotecario(email, senha);
            }
            else if (tipo_usuario == "Admin")
            {
                perfil_usuario = new Admin(email, senha);
            }

            if (perfil_usuario != nullptr)
            {
                // Add the Perfil_usuario to the usuarios map
                usuarios[email].push_back(perfil_usuario);
            }
        }
    }

    arquivo_usuarios.close();
}

int Sistema::tela_cadastro()
{
    std::cout << "ola" << std::endl;
    return 0;
}
