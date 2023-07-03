#include <iostream>
#include <string>
#include <exception>

#include "../include/bancodedados.h"

using namespace std;

// a mesma logica para todos os metodos bd_criar_tabela_.
void BD::bd_criar_tabela_acervos(const char* f){
    
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
void BD::bd_criar_tabela_usuarios(const char* f){
    
    sqlite3* bibdb; 
    sqlite3_open(f, &bibdb);

    string sql_comando = "CREATE TABLE IF NOT EXISTS Usuarios("
    "ID INT NOT NULL,"
    "email TEXT NOT NULL,"
    "senha INTEGER NOT NULL,"
    "papel TEXT)";

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
void BD::bd_criar_tabela_exemplares(const char* f){
    
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
void BD::bd_inserir_tabela_acervos(const char* f, Acervo livro){
    bool check = checkAcervo(f, livro);
    if(check == (0||false)){
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
}

void BD::bd_inserir_tabela_usuarios(const char*f, Perfil_usuario user){
    bool check = checkUsuario(f, user);
    if(check==(0||false)){
        sqlite3* bibdb;
        sqlite3_open(f, &bibdb);

        string email = user.get_email_perfil_usuario();
        int id = user.get_ID_perfil_usuario();
        int senha = user.get_senha_perfil_usuario();
        string papel = "indefinido";

        string sql_comando = "INSERT INTO Usuarios VALUES("+to_string(id)+",'"+email+"',"+to_string(senha)+",'"+papel+"');";

        char* msgerr;
        int rsp = 0;

        rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
        if (rsp!=SQLITE_OK){
            cerr << "ERRO AO INSERIR EM USUARIOS: " << msgerr << endl;
        }

        sqlite3_free(msgerr);
        sqlite3_close(bibdb);
    }
}

void BD::bd_inserir_admin(const char* f, Admin adm){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    bd_inserir_tabela_usuarios(f, adm);

    int admid = adm.get_ID_perfil_usuario();
    string papel = "administrador";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(admid)+"; ";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO INSERIR Admin EM Usuarios: " << msgerr << endl;
    }
    
    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

void BD::bd_inserir_aluno(const char* f, Aluno aluno){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    bd_inserir_tabela_usuarios(f, aluno);

    int alunoid = aluno.get_ID_perfil_usuario();
    string papel = "aluno";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(alunoid)+"; ";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO INSERIR aluno EM Usuarios: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);

}

void BD::bd_inserir_bibliotecario(const char* f, Bibliotecario bibliotecario){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    bd_inserir_tabela_usuarios(f, bibliotecario);
    int bibliotecarioid = bibliotecario.get_ID_perfil_usuario();
    string papel = "bibliotecario";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(bibliotecarioid)+";";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO INSERIR bibliotecario EM Usuarios: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}


void BD::bd_inserir_tabela_exemplares(const char* f, Exemplar item){

    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    string autor = item.getAutor(); 
    int anopub = item.getAnoPublicacao(); 
    string titulo = item.getTitulo(); 
    string genero = item.getGenero();
    int codigo = item.getCodigo();
    int emprestado = item.isEmprestado(); 
    int dataaquisicao = item.getDataAquisicao();
    int codigoespecifico = item.getCodigoEspecifico();
    int datadevolucao = item.getDataDevolucao();

    string sql_comando = "INSERT INTO Exemplares VALUES('"+autor+"',"+to_string(anopub)+",'"+titulo+"','"+genero+"',"+
    to_string(codigo)+","+to_string(emprestado)+","+to_string(dataaquisicao)+","+to_string(codigoespecifico)+","+
    to_string(datadevolucao)+");";

    char* msgerr;
    int rsp = 0;

    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if (rsp != SQLITE_OK){
        cerr << "ERRO AO INSERIR EM EXEMPLARES: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}


void BD::bd_acessar_tebela_acervos(const char* f){
    
    bool check = checkTabelaExiste(f, "Acervos");
    if(check==(1||true)){
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
    else{
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: Acervos" << endl;
    }
}

void BD::bd_acessar_tabela_usuarios(const char* f){
    
    bool check = checkTabelaExiste(f, "Usuarios");
    if(check==(1||true)){
        sqlite3* bibdb;
        sqlite3_open(f, &bibdb);
        sqlite3_stmt* stmt;

        string sql_comando = "SELECT * FROM Usuarios;";

        sqlite3_prepare_v2(bibdb, sql_comando.c_str(), -1, &stmt, 0);

        int id;
        const unsigned char* email;
        int senha;
        const unsigned char* papel;
        int numusuarios = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){
            
            id = sqlite3_column_int(stmt, 0);
            email = sqlite3_column_text(stmt, 1);
            senha = sqlite3_column_int(stmt, 2);
            papel = sqlite3_column_text(stmt, 3);
            numusuarios++;

            cout << "Usuario "+to_string(numusuarios)+": " << endl;
            cout << "id: " << id << endl;
            cout << "email: " << email << endl;
            cout << "senha: " << senha << endl;
            cout << "papel: " << papel << endl;
            cout << "\n";

        }

        sqlite3_free(stmt);
        sqlite3_close(bibdb);
    }
    else{
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: Usuarios" << endl;
    }

}

void BD::bd_acessar_tabela_exemplares(const char* f){

    bool check = checkTabelaExiste(f,"Exemplares");
    if(check==(1||true)){
        sqlite3* bibdb;
        sqlite3_open(f, & bibdb);
        sqlite3_stmt* stmt;

        string sql_consulta = "SELECT * FROM Exemplares;";

        sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

        const unsigned char* autor;
        const unsigned char* titulo;
        const unsigned char* genero;
        int emprestado, anopub, dataaquisicao, datadevolucao, codigo, codigospecifico;
        int numexemplares = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){

            autor = sqlite3_column_text(stmt, 0);
            anopub = sqlite3_column_int(stmt, 1);
            titulo = sqlite3_column_text(stmt, 2);
            genero = sqlite3_column_text(stmt, 3);
            codigo = sqlite3_column_int(stmt, 4);
            emprestado = sqlite3_column_int(stmt, 5);
            dataaquisicao = sqlite3_column_int(stmt, 6);
            codigospecifico = sqlite3_column_int(stmt, 7);
            datadevolucao = sqlite3_column_int(stmt,8);
            numexemplares++;

            cout << "Exemplar "+to_string(numexemplares)+": " << endl;
            cout << "autor: " << autor << endl;
            cout << "ano de publicacao: " << anopub << endl;
            cout << "titulo: " << titulo << endl;
            cout << "genero: " << genero << endl;
            cout << "codigo: " << codigo << endl;
            cout << "data de aquisicao: " << dataaquisicao << endl; 
            cout << "emprestado: " << emprestado << endl;
            cout << "data de devolucao: " << datadevolucao << endl;
            cout << "\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(bibdb);
    }
    else {
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: Exemplares" << endl;
    }
}

//metodos para destruir tabelas
void BD::bd_destruir_tabela_acervos(const char* f){
    sqlite3* bibdb;
    sqlite3_open(f,&bibdb);

    string sql_comando = "Drop Table Acervos;";
    char* msgerr;
    
    int rsp = 0;
    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(rsp!=SQLITE_OK){
        cerr << "ERRO AO DESTRUIR TABELA ACERVOS: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

void BD::bd_destruir_tabela_usuarios(const char* f){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    string sql_comando = "Drop Table Usuarios;";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO DESTRUIR TABELA USUARIOS: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

void BD::bd_destruir_tabela_exemplares(const char* f){
    
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    string sql_comando = "Drop Table Exemplares; ";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO DESTRUIR TABELA EXEMPLARES: " << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

//metodos para remover
void BD::bd_remover_acervo(const char* f, Acervo livro){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigoacervo = livro.getCodigo();

    string sql_comando = "Delete from Acervos where codigo="+to_string(codigoacervo)+"; ";
    char* msgerr;
    int rsp = 0;
    rsp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(rsp!=SQLITE_OK){
        cerr << "ERRO AO REMOVER ACERVO: " << msgerr << endl; 
    }

    //se um acervo eh removido seus exemplares tambem sao.
    Exemplar livroaux("",0,"","",codigoacervo,0,0,0,0);
    bd_remover_exemplar(f, livroaux);

    sqlite3_finalize(stmt);
    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

void BD::bd_remover_usuario(const char* f, Perfil_usuario user){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int iduser = user.get_ID_perfil_usuario();
    string sql_comando = "Delete from Usuarios where ID="+to_string(iduser)+"; ";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO REMOVER USUARIO: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

void BD::bd_remover_exemplar(const char* f, Exemplar item){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoexemplar = item.getCodigo();
    string sql_comando = "Delete from Exemplares where codigo="+to_string(codigoexemplar)+"; ";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL,&msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO AO REMOVER EXEMPLAR: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);
}

//metodos de checagem.
bool BD::checkAcervo(const char* f, Acervo livro){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigodoacervo = livro.getCodigo();

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

bool BD::checkUsuario(const char* f, Perfil_usuario user){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int iduser = user.get_ID_perfil_usuario();

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

int BD::checkNumExemplares(const char* f, Acervo livro){
    
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    int codigodoacervo = livro.getCodigo();
    string sql_consulta = "SELECT * FROM Exemplares; ";
    int numexemplares = 0;

    sqlite3_prepare_v2(bibdb,sql_consulta.c_str(), -1, &stmt, 0);
    int codigoexemplar = 0;
    int codigoespecifico = 0;
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        codigoexemplar = sqlite3_column_int(stmt, 4);
        codigoespecifico = sqlite3_column_int(stmt, 7);

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

bool BD::checkTabelaExiste(const char*f, string nome_tabela){
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

void BD::updateExemplarEmprestado(const char* f, Exemplar item, int umouzero){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoespecifico = item.getCodigoEspecifico();

    string sql_comando = "UPDATE Exemplares set emprestado="+to_string(umouzero)+" where ID="+to_string(codigoespecifico)+";";
    char* msgerr;
    int resp = 0;

    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
    if(resp!=SQLITE_OK){
        cerr << "ERRO ATUALIZAR Emprestado em Exemplares: " << msgerr << endl;
    }

    sqlite3_free(msgerr);
    sqlite3_close(bibdb);

}
