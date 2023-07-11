#include "../include/sistema.hpp"

Sistema::Sistema()
{
    // abre arquivo users, pega todos os users e deixa no ram
    // abre arquivo acervos, abre arquivo exemplares
    // pega acervos, PROCURA NO ARQUIVO INTEIRO se ele tem algum exemplar
    // tem: cadastra ele (se nao tiver exemplar continua um vetor vazio)
    carregar_acervos();
    carregar_exemplares();
    carregar_usuarios();
}

// Load exemplares from "exemplares.csv"
void carregar_exemplares()
{
    std::ifstream arquivo_exemplares("exemplares.csv");
    if (!arquivo_exemplares)
    {
        std::cout << "Falha ao abrir o arquivo exemplares.csv" << std::endl;
        return;
    }

    std::string linha;
    while (getline(arquivo_exemplares, linha))
    {
        std::istringstream iss(linha);
        std::string campo;

        // Parse exemplar fields
        std::string autor, titulo, ano_publicacao_str, genero_str, codigo_str, codigo_esp_string;
        if (getline(iss, codigo_str, ',') &&
            getline(iss, codigo_str, ',') &&
            getline(iss, autor, ',') &&
            getline(iss, titulo, ',') &&
            getline(iss, ano_publicacao_str, ',') &&
            getline(iss, genero_str, ',') &&)
        {
            int ano_publicacao = std::stoi(ano_publicacao_str);
            int genero = std::stoi(genero_str);
            int codigo = std::stoi(codigo_str);

            // Create an Exemplar object
            Exemplar *exemplar = new Exemplar(codigo, codigo_especifico, autor, titulo, genero);

            // Add the Exemplar to the biblioteca map
            Acervo acervo(autor, ano_publicacao, titulo, genero, codigo);
            biblioteca[acervo].push_back(exemplar);
        }
    }

    arquivo_exemplares.close();
}

// Load acervos from "acervos.csv"
void carregar_acervos()
{
    std::ifstream arquivo_acervos("acervos.csv");
    if (!arquivo_acervos)
    {
        std::cout << "Falha ao abrir o arquivo acervos.csv" << std::endl;
        return;
    }

    std::string linha;
    while (getline(arquivo_acervos, linha))
    {
        std::istringstream iss(linha);
        std::string campo;

        // Parse acervo fields
        std::string autor, titulo, ano_publicacao_str, genero_str, codigo_str;
        if (getline(iss, autor, ',') &&
            getline(iss, titulo, ',') &&
            getline(iss, ano_publicacao_str, ',') &&
            getline(iss, genero_str, ',') &&
            getline(iss, codigo_str, ','))
        {
            int ano_publicacao = std::stoi(ano_publicacao_str);
            int genero = std::stoi(genero_str);
            int codigo = std::stoi(codigo_str);

            // Create an Acervo object
            Acervo acervo(autor, ano_publicacao, titulo, genero, codigo);

            // Add the Acervo to the biblioteca map if it doesn't exist
            if (biblioteca.find(acervo) == biblioteca.end())
            {
                biblioteca[acervo] = std::vector<Exemplar>();
            }
        }
    }

    arquivo_acervos.close();
}

// Load usuarios from "usuarios.csv"
void carregar_usuarios()
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
        std::string tipo_usuario, email, senha_str;
        if (getline(iss, tipo_usuario, ',') &&
            getline(iss, email, ',') &&
            getline(iss, senha_str, ','))
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

            if (perfil_usuario != nullptr)
            {
                // Add the Perfil_usuario to the usuarios map
                usuarios[senha].push_back(perfil_usuario);
            }
        }
    }

    arquivo_usuarios.close();
}
}
;