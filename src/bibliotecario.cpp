#include "../include/bibliotecario.hpp"

Bibliotecario::Bibliotecario(std::string email, int senha) : Perfil_usuario(email, senha)
{
    _papel = BIBLIOTECARIO;
    salvar_bibl_no_arquivo();
    bd_criar_tabela_usuarios(file);
    bd_inserir_bibliotecario(file, this);
    bd_criar_tabela_acervos(file);
}

Bibliotecario::~Bibliotecario() {}

void Bibliotecario::consultar_acervo(std::string titulo) // pra bibliotecario retorna tudo sobre o acervo e quantidade de exemplares totais e emprestados
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
    Acervo livro(codigo,autor,titulo,ano_publicacao,genero);
    bd_inserir_tabela_acervos(file, &livro);
}

void Bibliotecario::adicionar_exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero)
{
    bd_criar_tabela_exemplares(file);
    Exemplar novo_exemplar = Exemplar(codigo, codigoEspecifico, autor, titulo, ano_publicacao, genero);
    bd_inserir_tabela_exemplares(file, &novo_exemplar);
}

void Bibliotecario::remover_acervo(int codigo_acervo)
{
    Acervo aux(codigo_acervo,"","",0000,0);
    bd_remover_acervo(file, &aux);


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
    Exemplar aux(0,codigo_exemplar,"","",0000,0);
    bool check = checkExemplarAluno(file, &aux);
    if(check==(0||false)){
        bd_remover_exemplarespecifico(file, &aux);
        bd_remover_exemplaraluno(file, codigo_exemplar);
    }

    std::ifstream arquivo_acervo("files/acervos.csv");
    std::ofstream arquivo_atualizado("files/acervos_temp.csv");

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


    remove("files/acervos.csv");
    rename("files/acervos_temp.csv", "files/acervos.csv");

}

void Bibliotecario::emprestimo_de_exemplar(Exemplar livro, Aluno aluno)
{

    try {
        aluno.emprestar_livro(&livro);
    } catch(ja_possui_mutos_livros_e) {
        std::cout << "O aluno ja possui muitos livros, nao pode pegar mais." << std::endl;
    } catch(ja_possui_esse_livro_e) {
        std::cout << "O aluno ja possui este livro." << std::endl;
    } catch(aluno_com_multa_e) {
        std::cout << "O aluno esta com multas, nao pode pegar mais livros até pagar." << std::endl;
    }
}

void Bibliotecario::devolucao_de_exemplar(int codigo, Aluno &aluno)
{
    try {
        aluno.devolver_livro(codigo);
    } catch(nao_possui_esse_livro_e) {
        std::cout << "O aluno não possui este livro." << std::endl;
    }
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

//PERSISTENCE
void Bibliotecario::executar_sql(const char* f, string comandosql, string avisoerro){
    
    //criando uma conexao com o banco de dados.
    sqlite3* bibdb;
    
    //abrindo o banco de dados.
    sqlite3_open(f, &bibdb);

    //comando para criar uma tabela, sintaxe sql.
    string sql_comando = comandosql;
    string alerta_erro = avisoerro;

    //para armazenar mensagens de erro e retorno da funcao, repsectivamente.
    char* msgerr;
    int resp = 0;

    //funcao que cria a tabela.
    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << alerta_erro << msgerr << endl;
    }
    
    //liberando memoria.
    sqlite3_free(msgerr);    
    sqlite3_close(bibdb);  
}

void Bibliotecario::bd_criar_tabela_acervos(const char* f){

    //comando para criar uma tabela, sintaxe sql.
    string sql_comando = "CREATE TABLE IF NOT EXISTS Acervos("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero INT NOT NULL,"
    "codigo INTEGER NOT NULL)";

    string aviso_erro = "ERRO AO CRIAR A TABELA ACERVOS: ";

    executar_sql(f, sql_comando, aviso_erro);    

}

void Bibliotecario::bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user){

    bool check = checkUsuario(f, user);
    //se nao existe um usuario com o mesmo id segue a execucao.
    if(check==(0||false)){
        sqlite3* bibdb;
        sqlite3_open(f, &bibdb);

        string email = user->get_email_perfil_usuario();
        int id = user->get_ID_perfil_usuario();
        int senha = user->get_senha_perfil_usuario();
        int papel = 9;

        string sql_comando = "INSERT INTO Usuarios VALUES("+to_string(id)+",'"+email+"',"+to_string(senha)+
        ","+to_string(papel)+");";

        string alerta_erro = "ERRO AO INSERIR EM USUARIOS: ";

        executar_sql(f, sql_comando, alerta_erro);

    }
}

void Bibliotecario::bd_inserir_tabela_acervos(const char* f, Acervo* livro){

    bool check = checkAcervo(f, livro);
    //se nao ha nenhum livro com o mesmo codigo, a execucao continua.
    if(check == (0||false)){
        //armazenando os atributos do acervo em variaveis para subtituir no comando sql.
        string autor, title;
        autor = livro->get_autor();
        title = livro->get_titulo();
        int genero = livro->get_genero();
        int anopub;
        int codigo;
        anopub = livro->get_ano_publicacao();
        codigo = livro->get_codigo();

        string sql_comando = "INSERT INTO Acervos VALUES('"+autor+"',"+to_string(anopub)+",'"+title+"',"+to_string(genero)+","+to_string(codigo)+");";

        string alerta_erro = "ERRO AO INSERIR EM ACERVOS: ";

        executar_sql(f, sql_comando, alerta_erro);
    }
}

void Bibliotecario::bd_criar_tabela_exemplares(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS Exemplares("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero INT NOT NULL,"
    "codigo INTEGER NOT NULL,"
    "codigoexemplar TEXT NOT NULL,"
    "emprestado INT NOT NULL)";

    string alerta_erro =  "ERRO AO CRIAR A TABELA ACERVOS: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Bibliotecario::bd_inserir_tabela_exemplares(const char* f, Exemplar* item){

    bool check = checkExemplar(f, item);
    if(check==(0||false)){
        string autor, titulo;
        autor = item->get_autor(); 
        int anopub = item->get_ano_publicacao(); 
        titulo = item->get_titulo(); 
        int genero = item->get_genero();
        int codigo = item->get_codigo();
        int codigo_exemplar = item->getCodigoEspecifico();
        int emprestado = 0;

        string sql_comando = "INSERT INTO Exemplares VALUES('"+autor+"',"+to_string(anopub)+",'"+titulo+"',"+to_string(genero)+","+
        to_string(codigo)+","+to_string(codigo_exemplar)+","+to_string(emprestado)+");";

        string alerta_erro = "ERRO AO INSERIR EM EXEMPLARES: ";

        executar_sql(f, sql_comando, alerta_erro);
    }
}

void Bibliotecario::bd_acessar_tabela_exemplares(const char* f){

    bool check = checkTabelaExiste(f,"Exemplares");

    if(check==(1||true)){

        sqlite3* bibdb;
        sqlite3_open(f, & bibdb);
        sqlite3_stmt* stmt;

        string sql_consulta = "SELECT * FROM Exemplares;";

        sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

        const unsigned char* autor;
        const unsigned char* titulo;
        const unsigned char* codigo_exemplar;
        int emprestado;
        int anopub, codigo, genero;
        int numexemplares = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){

            autor = sqlite3_column_text(stmt, 0);
            anopub = sqlite3_column_int(stmt, 1);
            titulo = sqlite3_column_text(stmt, 2);
            genero = sqlite3_column_int(stmt, 3);
            codigo = sqlite3_column_int(stmt, 4);
            codigo_exemplar = sqlite3_column_text(stmt, 5);
            emprestado = sqlite3_column_int(stmt, 6);
            numexemplares++;

            cout << "Exemplar "+to_string(numexemplares)+": " << endl;
            cout << "autor: " << autor << endl;
            cout << "ano de publicacao: " << anopub << endl;
            cout << "titulo: " << titulo << endl;
            cout << "genero: " << genero << endl;
            cout << "codigo: " << codigo << endl;
            cout << "codigo do exemplar: " << codigo_exemplar << endl; 
            cout << "emprestado: " << emprestado << endl;
            cout << "\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(bibdb);
    }
    else {
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: Exemplares" << endl;
    }
}

void Bibliotecario::bd_inserir_aluno(const char* f, Aluno* aluno){

    bd_inserir_tabela_usuarios(f, aluno);

    int alunoid = aluno->get_ID_perfil_usuario();
    int papel = 2;

    string sql_comando = "UPDATE Usuarios set papel="+to_string(papel)+" where ID="+to_string(alunoid)+"; ";

    string alerta_erro = "ERRO AO INSERIR aluno EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);

}


void Bibliotecario::bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item){

    unsigned int alunoid = aluno->get_ID_perfil_usuario();
    int codigoexemplar = item->getCodigoEspecifico();
    int multa = item->calculaMulta();

    string sql_comando = "INSERT INTO AlunosExemplares VALUES("+to_string(alunoid)+","+to_string(codigoexemplar)+","+
    to_string(multa)+");";

    string alerta_erro = "ERRO AO INSERIR EM AlunosExemplares: ";

    executar_sql(f, sql_comando, alerta_erro);
}



void Bibliotecario::bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno){

    bool check = checkTabelaExiste(f,"AlunosExemplares");
    
    if(check==(1||true)){

        sqlite3* bibdb;
        sqlite3_open(f, & bibdb);
        sqlite3_stmt* stmt;

        int id = aluno->get_ID_perfil_usuario();

        string sql_consulta = "SELECT * FROM AlunosExemplares where alunoid="+to_string(id)+";";

        sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

        const unsigned char* codigoexemplar;
        int alunoidbd, multaexemplar;
        int numexemplares = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){
            alunoidbd = sqlite3_column_int(stmt, 0);
            codigoexemplar = sqlite3_column_text(stmt, 1);
            multaexemplar = sqlite3_column_int(stmt,2);
            numexemplares++;

            cout << "Exemplar "+to_string(numexemplares)+": " << endl;
            cout << "alunoid: " << alunoidbd << endl;
            cout << "codigo do exemplar: " << codigoexemplar << endl;
            cout << "multa: " << multaexemplar << endl;
            cout << "\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(bibdb);
    }
    else {
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: AlunosExemplares" << endl;
    }
}

void Bibliotecario::bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario){

    bd_inserir_tabela_usuarios(f, bibliotecario);

    int bibliotecarioid = bibliotecario->get_ID_perfil_usuario();
    int papel = 0;

    string sql_comando = "UPDATE Usuarios set papel="+to_string(papel)+" where ID="+to_string(bibliotecarioid)+";";

    string alerta_erro = "ERRO AO INSERIR bibliotecario EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Bibliotecario::bd_remover_exemplarespecifico(const char* f, Exemplar* item){

    bool check = checkExemplar(f, item);
    if(check==(1||true)){

        int idexemplar = item->getCodigoEspecifico();
        int idacervo = item->get_codigo();

        string sql_comando = "Delete from Exemplares where codigoexemplar="+to_string(idexemplar)+"; ";
        string alerta_erro = "ERRO AO REMOVER EXEMPLAR ESPECIFICO: "+to_string(idexemplar)+
        "ACERVO CORRESPONDENTE: "+to_string(idacervo);

        executar_sql(f, sql_comando, alerta_erro);
    }
}

void Bibliotecario::bd_remover_exemplaraluno(const char *f, int exemplarid){

    int codigoexemplar = exemplarid;
    string sql_comando = "Delete from AlunosExemplares where codigoexemplar="+to_string(codigoexemplar)+"; ";
    string alerta_erro = "ERRO AO REMOVER EXEMPLAR: "+to_string(codigoexemplar);
    
    executar_sql(f, sql_comando, alerta_erro);
}

void Bibliotecario::bd_remover_exemplaresdoacervo(const char* f, Acervo* livro){

    bool check = checkAcervo(f, livro);

    if(check==(1||true)){

        int codigodolivro = livro->get_codigo();
        string sql_comando = "Delete from Exemplares where codigo="+to_string(codigodolivro)+"; ";
        string alerta_erro = "ERRO AO REMOVER OS EXEMPLARES DO ACERVO "+to_string(codigodolivro)+": ";
        executar_sql(f, sql_comando, alerta_erro);      
    }
    else{
        cerr << "ERRO AO REMOVER EXEMPLARES DE UM ACERVO INEXISTENTE: " << livro->get_codigo() << endl;
    }

}

void Bibliotecario::bd_remover_acervo(const char* f, Acervo *livro){

    bool check = checkAcervo(f, livro);
    if(check==(1||true)){

        int codigoacervo = livro->get_codigo();

        string sql_comando = "Delete from Acervos where codigo="+to_string(codigoacervo)+"; ";
        string alerta_erro = "ERRO AO REMOVER ACERVO: "; 
        executar_sql(f, sql_comando, alerta_erro);

        //se um acervo eh removido seus exemplares tambem sao. 
        bd_remover_exemplaresdoacervo(f, livro);
    }
    else{
        cerr << "ERRO AO REMOVER ACERVO INEXISTENTE: "<< livro->get_codigo() << endl;
    }
}

bool Bibliotecario::checkAcervo(const char* f, Acervo* livro){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigodoacervo = livro->get_codigo();

    // string sql_consulta = "SELECT FROM Acervos where codigo="+to_string(codigodoacervo)+" and titulo="+
    // tituloacervo+"; ";

    string sql_consulta = "SELECT * FROM Acervos; ";

    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);
    const unsigned char* tituloigual;
    int codigoigual = 0;

    while(sqlite3_step(stmt)!=SQLITE_DONE){
        tituloigual = sqlite3_column_text(stmt, 2);
        codigoigual = sqlite3_column_int(stmt, 4);

        if(codigoigual==codigodoacervo){
            // cout << "ERRO: Ja existe um acervo com esse codigo: "+to_string(codigoigual)+", Titulo: " << tituloigual <<"."<< endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;
    
}

bool Bibliotecario::checkUsuario(const char* f, Perfil_usuario* user){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int iduser = user->get_ID_perfil_usuario();

    string sql_consulta = "SELECT * FROM Usuarios; ";

    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);
    int idigual = 0;
    const unsigned char* emailigual;

    while(sqlite3_step(stmt)!=SQLITE_DONE){
        idigual = sqlite3_column_int(stmt, 0);
        emailigual = sqlite3_column_text(stmt, 1);

        if(idigual == iduser){
            // cout << "ERRO: Usuario ja cadastrado com id: "+to_string(idigual)+", email: " << emailigual << "." << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;
}

bool Bibliotecario::checkTabelaExiste(const char*f, string nome_tabela){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    string sql_consulta = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='"+nome_tabela+"'; ";
    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);
    
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        int algumdadoint = sqlite3_column_int(stmt, 0);
        const unsigned char* algumdadotext = sqlite3_column_text(stmt, 0);

        if((algumdadoint==0) || (algumdadotext==0)){
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return false;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return true;
}

bool Bibliotecario::checkExemplar(const char* f, Exemplar* item){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigo_exemplar_int;
    codigo_exemplar_int = item->getCodigoEspecifico();
    int codigodoacervo;
    codigodoacervo = item->get_codigo();

    string sql_consulta = "SELECT * FROM Exemplares; ";

    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

    int codigoexemplarbd;
    int codigodoacervobd;

    while(sqlite3_step(stmt)!=SQLITE_DONE){

        codigodoacervobd = sqlite3_column_int(stmt, 4);
        codigoexemplarbd = sqlite3_column_int(stmt,5);

        if(codigodoacervobd == codigodoacervo){
            if(codigo_exemplar_int == codigoexemplarbd){
                // cout << "ERRO: Ja existe um Exemplar com esse codigo especifico: "+to_string(codigoexemplarbd)+
                // ", Codigo do Acervo corresp.: " << codigodoacervobd << "." << endl;
                sqlite3_finalize(stmt);
                sqlite3_close(bibdb);
                return true;
            }
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;

}

bool Bibliotecario::checkExemplarAluno(const char* f, Exemplar* item){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigo_exemplar;
    codigo_exemplar = item->getCodigoEspecifico();

    string sql_consulta = "SELECT * FROM AlunosExemplares; ";

    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

    int codigoexemplarbd;
    int idalunobd;

    while(sqlite3_step(stmt)!=SQLITE_DONE){

        idalunobd = sqlite3_column_int(stmt, 0);
        codigoexemplarbd = sqlite3_column_int(stmt,1);

        if(codigo_exemplar == codigoexemplarbd){
            cout << "ERRO AO REMOVER EXEMPLAR: O exemplar - codigo especifico: "+to_string(codigoexemplarbd)+"." <<
            "Esta EMPRESTADO ao aluno: " << idalunobd << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;

}

void Bibliotecario::updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoespecifico = item->getCodigoEspecifico();

    string sql_comando = "UPDATE Exemplares set emprestado="+to_string(umouzero)+" where codigoexemplar="+to_string(codigoespecifico)+";";
    string alerta_erro = "ERRO AO ATUALIZAR Emprestado em Exemplares: "+to_string(codigoespecifico);

    executar_sql(f, sql_comando, alerta_erro);

}

void Bibliotecario::UpdateMultaExemplarAluno(const char* f, Exemplar* item){

    int multadoexemplar = item->calculaMulta();
    int iddoexemplar = item->getCodigoEspecifico();

    string sql_comando = "UPDATE AlunosExemplares set multa="+to_string(multadoexemplar)+" where codigoexemplar="+
    to_string(iddoexemplar)+"; ";

    string alerta_erro = "ERRO AO ATUALIZAR multa em AlunosExemplares: ";
    
    executar_sql(f, sql_comando, alerta_erro);

}
