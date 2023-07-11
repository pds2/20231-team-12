#include "../include/perfil_usuario.hpp"

unsigned int Perfil_usuario::CONTADOR_ID_perfil_usuario = 0;

Perfil_usuario::Perfil_usuario()
{
    _ID_perfil_usuario = 99999;
    _email_perfil_usuario = ("VAZIO");
    _senha_pefil_usuario = 99999;
    _papel = ALUNO;
    bd_criar_tabela_usuarios(file);
}

Perfil_usuario::~Perfil_usuario() {}

Perfil_usuario::Perfil_usuario(std::string email, int senha) : _email_perfil_usuario(email), _senha_pefil_usuario(senha)
{
    _ID_perfil_usuario = CONTADOR_ID_perfil_usuario;
    CONTADOR_ID_perfil_usuario++;
    bd_criar_tabela_usuarios(file);
    bd_inserir_tabela_usuarios(file, this);
}

Papel_do_usuario Perfil_usuario::get_papel_usuario()
{
    return this->_papel;
}

unsigned int Perfil_usuario::get_ID_perfil_usuario()
{
    return this->_ID_perfil_usuario;
}

std::string Perfil_usuario::get_email_perfil_usuario()
{
    return this->_email_perfil_usuario;
}

int Perfil_usuario::get_senha_perfil_usuario()
{
    return this->_senha_pefil_usuario;
}

//PERSISTENCE

void Perfil_usuario::executar_sql(const char* f, string comandosql, string avisoerro){
    
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

void Perfil_usuario::bd_criar_tabela_usuarios(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS Usuarios("
    "ID INT NOT NULL,"
    "email TEXT NOT NULL,"
    "senha INTEGER NOT NULL,"
    "papel TEXT)";

    string alerta_erro = "ERRO AO CRIAR A TABELA USUARIOS: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Perfil_usuario::bd_criar_tabela_exemplaresaluno(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS AlunoExemplares("
    "alunoid INT NOT NULL,"
    "codigoexemplar TEXT NOT NULL,"
    "multa INT NOT NULL)";

    string alerta_erro = "ERRO AO CRIAR A TABELA ALUNOEXEMPLARES: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Perfil_usuario::bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user){

    bool check = checkUsuario(f, user);
    //se nao existe um usuario com o mesmo id segue a execucao.
    if(check==(0||false)){
        sqlite3* bibdb;
        sqlite3_open(f, &bibdb);

        string email = user->get_email_perfil_usuario();
        int id = user->get_ID_perfil_usuario();
        int senha = user->get_senha_perfil_usuario();
        string papel = "indefinido";

        string sql_comando = "INSERT INTO Usuarios VALUES("+to_string(id)+",'"+email+"',"+to_string(senha)+",'"+papel+"');";

        string alerta_erro = "ERRO AO INSERIR EM USUARIOS: ";

        executar_sql(f, sql_comando, alerta_erro);

    }
}


void Perfil_usuario::bd_destruir_tabela_usuarios(const char* f){

    string sql_comando = "Drop Table Usuarios;";
    string alerta_erro = "ERRO AO DESTRUIR TABELA USUARIOS: ";
    executar_sql(f, sql_comando, alerta_erro);

}

bool Perfil_usuario::checkUsuario(const char* f, Perfil_usuario* user){

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
            cout << "ERRO: Usuario ja cadastrado com id: "+to_string(idigual)+", email: " << emailigual << "." << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;
}

bool Perfil_usuario::checkTabelaExiste(const char*f, string nome_tabela){

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