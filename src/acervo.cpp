#include "../include/acervo.h"

Acervo::Acervo(std::string autor, int ano_publicacao, std::string titulo,
               int genero, int codigo) : _autor(autor),
                                         _ano_publicacao(ano_publicacao),
                                         _titulo(titulo),
                                         _genero(genero),
                                         _codigo(codigo)
{
    bd_criar_tabela_acervos(file);
    bd_inserir_tabela_acervos(file, this);
}

std::string Acervo::get_autor() const
{
    return _autor;
}

int Acervo::get_ano_publicacao() const
{
    return _ano_publicacao;
}

std::string Acervo::get_titulo() const
{
    return _titulo;
}

int Acervo::get_genero() const
{
    return _genero;
}

int Acervo::get_codigo() const
{
    return _codigo;
}

int Acervo::salvar_acervo_no_arquivo()
{
    std::ofstream acervo_out;
    acervo_out.open("acervos.csv", std::ios::app);
    if (!acervo_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;                                                            
    }
    else
    {
        acervo_out >> this->_codigo >> this->_titulo >> this->_autor >> this->_ano_publicacao >> this->_genero;
        acervo_out.close();
        return 1;
    }
}


//PERSISTENCE:

void Acervo::executar_sql(const char* f, string comandosql, string avisoerro){
    
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

void Acervo::bd_criar_tabela_acervos(const char* f){

    //comando para criar uma tabela, sintaxe sql.
    string sql_comando = "CREATE TABLE IF NOT EXISTS Acervos("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero TEXT NOT NULL,"
    "codigo INTEGER NOT NULL)";

    string aviso_erro = "ERRO AO CRIAR A TABELA ACERVOS: ";

    executar_sql(f, sql_comando, aviso_erro);    

}

void Acervo::bd_inserir_tabela_acervos(const char* f, Acervo* livro){

    bool check = checkAcervo(f, livro);
    //se nao ha nenhum livro com o mesmo codigo, a execucao continua.
    if(check == (0||false)){
        //armazenando os atributos do acervo em variaveis para subtituir no comando sql.
        string autor, title, genero;
        autor = livro->get_autor();
        title = livro->get_titulo();
        genero = livro->get_genero();
        int anopub;
        int codigo;
        anopub = livro->get_ano_publicacao();
        codigo = livro->get_codigo();

        string sql_comando = "INSERT INTO Acervos VALUES('"+autor+"',"+to_string(anopub)+",'"+title+"','"+genero+"',"+to_string(codigo)+");";

        string alerta_erro = "ERRO AO INSERIR EM ACERVOS: ";

        executar_sql(f, sql_comando, alerta_erro);
    }
}
 
void Acervo::bd_acessar_tebela_acervos(const char* f){

    bool check = checkTabelaExiste(f, "Acervos");
    //se a tabela existe, continua a execucao.
    if(check==(1||true)){

        sqlite3* bibdb;
        sqlite3_open(f, &bibdb);
        sqlite3_stmt* stmt;

        string sql_consulta = "SELECT * FROM Acervos;";

        sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

        int anopub, codigo;
        const unsigned char* autor;
        const unsigned char* titulo;
        const unsigned char* genero;
        int numacervo = 0;

        while (sqlite3_step(stmt) != SQLITE_DONE) {
            autor = sqlite3_column_text(stmt, 0);
            anopub = sqlite3_column_int(stmt, 1);
            titulo = sqlite3_column_text(stmt, 2);
            genero = sqlite3_column_text(stmt, 3);
            codigo = sqlite3_column_int(stmt, 4);
            numacervo++;

            cout << "Acervo "+to_string(numacervo)+": " << endl;
            cout << "autor: " << autor << endl;
            cout << "ano de publicacao: " << anopub << endl;
            cout << "titulo: " << titulo << endl;
            cout << "genero: " << genero << endl;
            cout << "codigo: " << codigo << endl;
            cout << "\n";

        }

        sqlite3_finalize(stmt);
        sqlite3_close(bibdb);        
    }
    //se a tabela foi destruida ou nao criada, else.
    else{
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: Acervos" << endl;
    }
}

void Acervo::bd_destruir_tabela_acervos(const char* f){

    string sql_comando = "Drop Table Acervos;";
    string alerta_erro = "ERRO AO DESTRUIR TABELA ACERVOS: ";
    executar_sql(f, sql_comando, alerta_erro);

}

void Acervo::bd_remover_acervo(const char* f, Acervo *livro){

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

void Acervo::bd_remover_exemplaresdoacervo(const char* f, Acervo* livro){

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

bool Acervo::checkAcervo(const char* f, Acervo* livro){

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
            cout << "ERRO: Ja existe um acervo com esse codigo: "+to_string(codigoigual)+", Titulo: " << tituloigual <<"."<< endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;
    
}

int Acervo::checkNumExemplares(const char* f, Acervo* livro){
    
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigodoacervo = livro->get_codigo();
    string sql_consulta = "SELECT * FROM Exemplares; ";
    int numexemplares = 0;

    sqlite3_prepare_v2(bibdb,sql_consulta.c_str(), -1, &stmt, 0);
    int codigoexemplar = 0;
    int codigoespecifico = 0;
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        codigoexemplar = sqlite3_column_int(stmt, 4);
        codigoespecifico = sqlite3_column_int(stmt, 5);

        if(codigodoacervo == codigoexemplar){
            numexemplares++;
            if(numexemplares == 1){
                cout << "Acervo "<< codigodoacervo << ":" << endl;
            }
            cout << "Exemplar " << numexemplares << ": " << codigoespecifico << "." << endl;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);
    
    return numexemplares;

}

bool Acervo::checkTabelaExiste(const char*f, string nome_tabela){

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
