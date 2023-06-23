#include <iostream>
#include <string>

#include "../include/bancodedados.h"

using namespace std;

BD::BD() {}

// a mesma logica para todos os metodos bd_criar_tabela_.
int BD::bd_criar_tabela_acervos(const char* f){
    
    //criando uma conexao com o banco de dados.
    sqlite3* bibdb;
    
    //abrindo o banco de dados.
    sqlite3_open(f, &bibdb);

    //comando para criar uma tabela, sintaxe sql.
    string sql_comando = "CREATE TABLE IF NOT EXISTS Acervos("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero TEXT NOT NULL,"
    "codigo INTEGER NOT NULL)";

    //para armazenar mensagens de erro e retorno da funcao, repsectivamente.
    char* msgerr;
    int rsp = 0;

    //funcao que cria a tabela.
    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(rsp!=SQLITE_OK){
        cerr << "ERRO AO CRIAR A TABELA ACERVOS: " << msgerr << endl;
    }
    
    //liberando memoria.
    sqlite3_free(msgerr);    
    sqlite3_close(bibdb);  
}

// a mesma logica para todos os metodos bd_criar_tabela_.
int BD::bd_criar_tabela_usuarios(const char* f){
    
    sqlite3* bibdb;
    
    sqlite3_open(f, &bibdb);

    string sql_comando = "CREATE TABLE IF NOT EXISTS Usuarios("
    "ID INT NOT NULL,"
    "email TEXT NOT NULL,"
    "senha INTEGER NOT NULL)";

    char* msgerr;
    int rsp = 0;

    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(rsp!=SQLITE_OK){
        cerr << "ERRO AO CRIAR A TABELA USUARIOS: " << msgerr << endl;
    }
    
    sqlite3_free(msgerr);    
    sqlite3_close(bibdb);  
}

// a mesma logica para todos os metodos bd_criar_tabela_.
int BD::bd_criar_tabela_exemplares(const char* f){
    
    sqlite3* bibdb;
    
    sqlite3_open(f, &bibdb);

    string sql_comando = "CREATE TABLE IF NOT EXISTS Exemplares("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero TEXT NOT NULL,"
    "codigo INTEGER NOT NULL,"
    "emprestado TEXT NOT NULL,"
    "dataaquisicao INTEGER NOT NULL,"
    "codigoespecificacao INTEGER NOT NULL,"
    "datadevolucao INTEGER NOT NULL)";

    char* msgerr;
    int rsp = 0;

    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(rsp!=SQLITE_OK){
        cerr << "ERRO AO CRIAR A TABELA ACERVOS: " << msgerr << endl;
    }
    
    sqlite3_free(msgerr);    
    sqlite3_close(bibdb);  
}

//a mesma logica para todos os metodos bd_inserir_tabela_.
int BD::bd_inserir_tabela_acervos(const char* f, Acervo livro){
    
    //criando conexao e abrindo o banco de dados.
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    //armazenando os atributos do acervo em variaveis para subtituir no comando sql.
    string autor, title, genero;
    autor = livro.getAutor();
    title = livro.getTitulo();
    genero = livro.getGenero();
    int anopub;
    int codigo;
    anopub = livro.getAnoPublicacao();
    codigo = livro.getCodigo();

    string sql_comando = "INSERT INTO Acervos VALUES('"+autor+"',"+to_string(anopub)+",'"+title+"','"+genero+"',"+to_string(codigo)+");";

    char* msgerr;
    int rsp = 0;

    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if (rsp!=SQLITE_OK){
        cerr << "ERRO AO INSERIR EM ACERVOS: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}


int BD::bd_inserir_tabela_usuarios(const char*f, Perfil_usuario user){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    string email = user.get_email_perfil_usuario();
    int id = user.get_ID_perfil_usuario();
    int senha = user.get_senha_perfil_usuario();

    string sql_comando = "INSERT INTO Usuarios VALUES("+to_string(id)+",'"+email+"',"+to_string(senha)+");";

    char* msgerr;
    int rsp = 0;

    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if (rsp!=SQLITE_OK){
        cerr << "ERRO AO INSERIR EM USUARIOS: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}


int BD::bd_acessar_tebela_acervos(const char* f){
    
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    /*stmt:
    Pense em cada instrução SQL como um programa de computador separado. 
    O texto SQL original é o código-fonte. Um objeto de instrução preparado é o código de objeto compilado. 
    Todo o SQL deve ser convertido em uma instrução preparada antes de ser executado.
    */
    sqlite3_stmt* stmt;

    string sql_consulta = "SELECT * FROM Acervos;";

    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

    int anopub, codigo;
    const unsigned char* autor;
    const unsigned char* titulo;
    const unsigned char* genero;

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        autor = sqlite3_column_text(stmt, 0);
        anopub = sqlite3_column_int(stmt, 1);
        titulo = sqlite3_column_text(stmt, 2);
        genero = sqlite3_column_text(stmt, 3);
        codigo = sqlite3_column_int(stmt, 4);

        cout << "Novo Acervo: " << endl;
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

int BD::bd_acessar_tabela_usuarios(const char* f){
    
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    string sql_comando = "SELECT * FROM Usuarios;";

    sqlite3_prepare_v2(bibdb, sql_comando.c_str(), -1, &stmt, 0);

    int id;
    const unsigned char* email;
    int senha;

    while(sqlite3_step(stmt)!=SQLITE_DONE){
        
        id = sqlite3_column_int(stmt, 0);
        email = sqlite3_column_text(stmt, 1);
        senha = sqlite3_column_int(stmt, 2);

        cout << "Novo Usuario: " << endl;
        cout << "id: " << id << endl;
        cout << "email: " << email << endl;
        cout << "senha: " << senha << endl;
        cout << "\n";

    }

    sqlite3_free(stmt);
    sqlite3_close(bibdb);

}