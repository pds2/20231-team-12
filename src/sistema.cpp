#include "../include/sistema.hpp"

Sistema::Sistema()
{
    // abre arquivo users, pega todos os users e deixa no ram
    // abre arquivo acervos, abre arquivo exemplares
    // pega acervos, PROCURA NO ARQUIVO INTEIRO se ele tem algum exemplar
    // tem: cadastra ele (se nao tiver exemplar continua um vetor vazio)
    // FEITO
}

void Sistema::inicia_sistema()
{
    std::cout << "ola! Bem vindo ao sistema de biblioteca do grupo 12.\n"
              << std::endl;

    std::cout << "carregando livros:\n"
              << std::endl;
    carregar_acervos();

    std::cout << "carregando usuarios:\n"
              << std::endl;
    carregar_usuarios();

    int i = tela_cadastro();
    if (i == 1)
    {
        int l = tela_login();
    }
}

Sistema::~Sistema()
{
    for (auto &pair : usuarios)
    {
        delete pair.second;
    }
}

// ESSE CODIGO NAO É EFICIENTE
void Sistema::carregar_acervos()
{

    // carrega os dois arquivos
    std::ifstream arquivo_acervos("files/acervos.csv");
    if (!arquivo_acervos)
    {
        std::cout << "Falha ao abrir o arquivo acervos.csv" << std::endl;
        std::__throw_bad_exception(); // trocar isso por um erro de verdade pessoal
    }
    std::ifstream arquivo_exemplares("files/exemplares.csv");
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
        std::string autor, titulo, ano_publicacao_str, genero, codigo_acervo_str;
        int ano_publicacao, codigo_acervo;
        if (getline(iss, codigo_acervo_str, ',') &&
            getline(iss, autor, ',') &&
            getline(iss, titulo, ',') &&
            getline(iss, ano_publicacao_str, ',') &&
            getline(iss, genero, '\n'))
        {
            ano_publicacao = std::stoi(ano_publicacao_str);
            codigo_acervo = std::stoi(codigo_acervo_str);

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
                    int codigo_exemplar = std::stoi(codigo_exemplar_str);
                    int codigo_especifico = std::stoi(codigo_esp_string);

                    Exemplar exemplar = Exemplar(codigo_exemplar, codigo_especifico, autor, titulo, ano_publicacao, genero_str);
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
    std::ifstream arquivo_usuarios("files/usuarios.csv");
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
            getline(iss, ID_udusario, '\n'))
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
                usuarios[email] = perfil_usuario;
            }
        }
    }

    arquivo_usuarios.close();
}

int Sistema::tela_cadastro()
{
    int entrada = 0;
    std::cout << "possui cadastro? 0 - nao, 1 - sim:\n"
              << std::endl;
    std::cin >> entrada;
    if (entrada == 0)
    {
        std::string email;
        int senha;
        std::cout << "Cadastre seu email:" << std::endl;
        std::cin >> email;
        std::cout << "Cadastre sua senha (somente números):" << std::endl;
        std::cin >> senha;

        Aluno *novo_aluno = new Aluno(email, senha); // sempre cria so aluno
        try
        {
            for (const auto &pair : usuarios)
            {

                if (novo_aluno->get_email_perfil_usuario() == usuarios.at(email)->get_email_perfil_usuario())
                {
                    throw email_ja_cadastrado_e();
                }
            }
            this->usuarios[email] = novo_aluno;
            // tratar excessoes, senha negativa
            return 1;
        }
        catch (email_ja_cadastrado_e &e)
        {
            delete novo_aluno;
        }
        if (entrada == 1)
        {
            return 1;
        }

        return 0;
    }
    return 0;
}

int Sistema::tela_login()
{
    std::string email;
    int senha;

    std::cout << "Digite seu email:" << std::endl;
    std::cin >> email;
    std::cout << "Digite sua senha (somente números):" << std::endl;
    std::cin >> senha;

    auto it = usuarios.find(email);
    if (it != usuarios.end())
    {
        Perfil_usuario *perfil = it->second;
        if (perfil->get_senha_perfil_usuario() == senha)
        {
            if (perfil->get_papel_usuario() == 2)
            {
                Aluno *aluno = new Aluno(email, senha);
                tela_aluno(*aluno);
            }
            else if (perfil->get_papel_usuario() == 1)
            {
                Bibliotecario *bibliotecario = new Bibliotecario(email, senha);
                tela_bibliotecario(*bibliotecario);
            }
            else if (perfil->get_papel_usuario() == 0)
            {
                Admin *admin = new Admin(email, senha);
                tela_admin(*admin);
            }
        }
    }

    else
    {
        int resposta;
        std::cout << "Email não encontrado\nDeseja fazer cadastro? 0 - não, 1 - sim" << std::endl;
        std::cin >> resposta;
        if (resposta == 1)
        {
            tela_cadastro();
        }
        else if (resposta == 0)
        {
            std::cout << "até mais!!" << std::endl;
        }
    }

    return 0; // login falhado
}

void Sistema::tela_aluno(Aluno &aluno)
{
    int entrada_aluno;
    std::cout << "Olá aluno!" << std::endl;
    std::cout << "Digite 1 para consultar seus livros:\nDigite 2 para consultar um livro específico:\nDigite 3 para sair:" << std::endl;
    std::cin >> entrada_aluno;
    std::string titulo_pesquisa;
    switch (entrada_aluno)
    {
    case 1:
        std::cout << "Livros com você:" << std::endl;
        aluno.get_livros_com_aluno();
        break;
    case 2:
        std::cout << "Digite o título do livro (não use virgulas nem acentos):" << std::endl;
        std::cin >> titulo_pesquisa;
        aluno.consultar_acervo(titulo_pesquisa);
        break;

    default:
        std::cout << "Até logo!!" << std::endl;
        break;
    }
}

void printa_opcoes_biblotecario()
{
    std::cout << "digite 1 para consultar todos os livros\n";
    std::cout << "digite 2 para consultar um livro\n";
    std::cout << "digite 3 para adicionar um livro\n";
    std::cout << "digite 4 para remover um livro\n";
    std::cout << "digite 5 para adicionar um exemplar\n";
    std::cout << "digite 6 para remover um exemplar\n";
    // std::cout << "digite 7 para ver todas as multas\n";
    std::cout << "digite 0 para sair\n";
    std::cout << "> ";
}

void Sistema::tela_bibliotecario(Bibliotecario &bibl)
{
    std::string op;
    std::cout << "Olá " << bibl.get_email_perfil_usuario() << std::endl;
    printa_opcoes_biblotecario();
    std::cin >> op;

    int op1;
    std::istringstream is(op);
    while (is >> op1)
    {
        switch (op1)
        {
        case 0:
        {
            exit(0);
        }
        case 1:
        {
            bibl.consultar_acervo();
            break;
        }
        case 2:
        {
            std::string t;
            std::cin >> t;
            bibl.consultar_acervo(t);
            break;
        }
        case 3:
        {
            std::string linha_acervo;
            std::string codigo_str, autor, titulo, ano_publicacao_str, genero;
            int codigo, ano_publicacao;

            std::cout << "Digite na ordem (codigo,autor,titulo,ano publicacao,genero):\n";
            std::cin >> linha_acervo;
            std::istringstream iss(linha_acervo);

            if (getline(iss, codigo_str, ',') &&
                getline(iss, autor, ',') &&
                getline(iss, titulo, ',') &&
                getline(iss, ano_publicacao_str, ',') &&
                getline(iss, genero, '\n'))
            {
                ano_publicacao = std::stoi(ano_publicacao_str);
                codigo = std::stoi(codigo_str);

                Acervo a(codigo, autor, titulo, ano_publicacao, genero);
                bibl.adicionar_acervo(a);
            }

            break;
        }
        case 4:
        {
            int codigo;
            std::cout << "Qual o codigo do livro que deseja remover?\n";
            std::cin >> codigo;
            bibl.remover_acervo(codigo);
            break;
        }
        case 5:
        {
            std::string linha_acervo;
            std::cout << "Digite na ordem (codigo,autor,titulo,ano publicacao,genero):\n";
            std::cin >> linha_acervo;

            std::istringstream iss(linha_acervo);
            std::string autor, titulo, ano_publicacao_str, genero_str, codigo_exemplar_str,
                codigo_esp_string;
            int ano_publicacao, codigo_exemplar, codigo_especifico;

            if (getline(iss, codigo_exemplar_str, ',') &&
                getline(iss, codigo_esp_string, ',') &&
                getline(iss, autor, ',') &&
                getline(iss, titulo, ',') &&
                getline(iss, ano_publicacao_str, ',') &&
                getline(iss, genero_str, '\n'))
            {
                ano_publicacao = std::stoi(ano_publicacao_str);
                codigo_exemplar = std::stoi(codigo_exemplar_str);
                codigo_especifico = std::stoi(codigo_esp_string);

                Exemplar e(codigo_exemplar, codigo_especifico, autor, titulo, ano_publicacao, genero_str);
                bibl.adicionar_exemplar(e);
            }
            break;
        }
        case 6:
        {
            int codigo;
            std::cout << "Qual o codigo do livro que deseja remover?\n";
            std::cin >> codigo;

            bibl.remover_exemplar(codigo);
            break;
        }
        }
    }
}

void Sistema::tela_admin(Admin &admin)
{
    int entrada_admin, senha_usuario;
    std::string email_usuario;
    std::cout << "Olá administrador!" << std::endl;
    std::cout << "Digite 1 para adicionar um bibliotecario:\nDigite 2 para remover um bibliotecario:\nDigite 3 para remover um aluno:\nDigite 4 para sair:" << std::endl;
    std::cin >> entrada_admin;
    switch (entrada_admin)
    {
    case 1:
        std::cout << "Digite o email do bibliotecario:" << std::endl;
        std::cin >> email_usuario;
        std::cout << "Digite a senha do bibliotecario:" << std::endl;
        std::cin >> senha_usuario;
        admin.adicionar_usuario(0, email_usuario, senha_usuario);
        break;
    case 2:
        std::cout << "Digite o email do bibliotecario:" << std::endl;
        std::cin >> email_usuario;
        admin.deletar_usuario(email_usuario);
        break;
    case 3:
        std::cout << "Digite o email do aluno:" << std::endl;
        std::cin >> email_usuario;
        admin.deletar_usuario(email_usuario);
    default:
        std::cout << "Até logo!!" << std::endl;
        break;
    }
}
