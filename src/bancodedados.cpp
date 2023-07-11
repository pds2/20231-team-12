#include <iostream>
#include <string>
#include <exception>

#include "../include/bancodedados.h"

using namespace std;

void BD::executar_sql(const char* f, string comandosql, string avisoerro){
    
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

void BD::bd_criar_tabela_acervos(const char* f){

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

void BD::bd_criar_tabela_usuarios(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS Usuarios("
    "ID INT NOT NULL,"
    "email TEXT NOT NULL,"
    "senha INTEGER NOT NULL,"
    "papel TEXT)";

    string alerta_erro = "ERRO AO CRIAR A TABELA USUARIOS: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_criar_tabela_exemplares(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS Exemplares("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero TEXT NOT NULL,"
    "codigo INTEGER NOT NULL,"
    "codigoexemplar TEXT NOT NULL,"
    "emprestado TEXT NOT NULL)";

    string alerta_erro =  "ERRO AO CRIAR A TABELA ACERVOS: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_criar_tabela_exemplaresaluno(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS AlunoExemplares("
    "alunoid INT NOT NULL,"
    "codigoexemplar TEXT NOT NULL,"
    "multa INT NOT NULL)";

    string alerta_erro = "ERRO AO CRIAR A TABELA ALUNOEXEMPLARES: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_inserir_tabela_acervos(const char* f, Acervo* livro){

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

void BD::bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user){

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

void BD::bd_inserir_admin(const char* f, Admin* adm){

    bd_inserir_tabela_usuarios(f, adm);

    int admid = adm->get_ID_perfil_usuario();
    string papel = "ADMIN";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(admid)+"; ";

    string alerta_erro = "ERRO AO INSERIR Admin EM Usuarios: ";
    
    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_inserir_aluno(const char* f, Aluno* aluno){

    bd_inserir_tabela_usuarios(f, aluno);

    int alunoid = aluno->get_ID_perfil_usuario();
    string papel = "ALUNO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(alunoid)+"; ";

    string alerta_erro = "ERRO AO INSERIR aluno EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);

}

void BD::bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario){

    bd_inserir_tabela_usuarios(f, bibliotecario);

    int bibliotecarioid = bibliotecario->get_ID_perfil_usuario();
    string papel = "BIBLIOTECARIO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(bibliotecarioid)+";";

    string alerta_erro = "ERRO AO INSERIR bibliotecario EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_inserir_tabela_exemplares(const char* f, Exemplar* item){

    string autor, titulo, genero;
    autor = item->get_autor(); 
    int anopub = item->get_ano_publicacao(); 
    titulo = item->get_titulo(); 
    genero = item->get_genero();
    int codigo = item->get_codigo();
    int codigo_exemplar = item->getCodigoEspecifico();

    string sql_comando = "INSERT INTO Exemplares VALUES('"+autor+"',"+to_string(anopub)+",'"+titulo+"','"+genero+"',"+
    to_string(codigo)+","+to_string(codigo_exemplar)+");";

    string alerta_erro = "ERRO AO INSERIR EM EXEMPLARES: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item){

    int alunoid = aluno->get_ID_perfil_usuario();
    int codigoexemplar = item->getCodigoEspecifico();
    int multa = item->calculaMulta();

    string sql_comando = "INSERT INTO AlunoExemplares VALUES("+to_string(alunoid)+","+to_string(codigoexemplar)+","+
    to_string(multa)+"); ";

    string alerta_erro = "ERRO AO INSERIR EM ALUNOEXEMPLARES: ";

    executar_sql(f, sql_comando, alerta_erro);
}
 
void BD::bd_acessar_tebela_acervos(const char* f){

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
        const unsigned char* codigo_exemplar;
        const unsigned char* emprestado;
        int anopub, codigo;
        int numexemplares = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){

            autor = sqlite3_column_text(stmt, 0);
            anopub = sqlite3_column_int(stmt, 1);
            titulo = sqlite3_column_text(stmt, 2);
            genero = sqlite3_column_text(stmt, 3);
            codigo = sqlite3_column_int(stmt, 4);
            codigo_exemplar = sqlite3_column_text(stmt, 5);
            emprestado = sqlite3_column_text(stmt, 6);
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

void BD::bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno){

    bool check = checkTabelaExiste(f,"AlunoExemplares");
    
    if(check==(1||true)){

        sqlite3* bibdb;
        sqlite3_open(f, & bibdb);
        sqlite3_stmt* stmt;

        int id = aluno->get_ID_perfil_usuario();

        string sql_consulta = "SELECT * FROM AlunoExemplares where alunoid="+to_string(id)+";";

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
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: AlunoExemplares" << endl;
    }
}

void BD::bd_destruir_tabela_acervos(const char* f){

    string sql_comando = "Drop Table Acervos;";
    string alerta_erro = "ERRO AO DESTRUIR TABELA ACERVOS: ";
    executar_sql(f, sql_comando, alerta_erro);

}

void BD::bd_destruir_tabela_usuarios(const char* f){

    string sql_comando = "Drop Table Usuarios;";
    string alerta_erro = "ERRO AO DESTRUIR TABELA USUARIOS: ";
    executar_sql(f, sql_comando, alerta_erro);

}

void BD::bd_destruir_tabela_exemplares(const char* f){

    string sql_comando = "Drop Table Exemplares; ";
    string alerta_erro = "ERRO AO DESTRUIR TABELA EXEMPLARES: ";
    executar_sql(f, sql_comando, alerta_erro);

}

void BD::bd_remover_acervo(const char* f, Acervo *livro){

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

void BD::bd_remover_usuario(const char* f, Perfil_usuario* user){

    int iduser = user->get_ID_perfil_usuario();
    string sql_comando = "Delete from Usuarios where ID="+to_string(iduser)+"; ";
    string alerta_erro = "ERRO AO REMOVER USUARIO: "+to_string(iduser)+" ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_remover_usuarioporid(const char* f, int id){

    string sql_comando = "Delete from Usuarios where ID="+to_string(id)+"; ";
    string alerta_erro = "ERRO AO REMOVER USUARIO: "+to_string(id)+" ";

    executar_sql(f, sql_comando, alerta_erro);
}

void BD::bd_remover_usuarioporemail(const char* f, string email){

    string sql_comando = "Delete from Usuarios where email="+email+"; ";
    string alerta_erro = "ERRO AO REMOVER USUARIO: "+email+" ";

    executar_sql(f, sql_comando, alerta_erro); 
}

void BD::bd_remover_aluno_e_devolver_exemplares(const char* f, Aluno *user){

    user->BDauxiliar("Persistence20231");
    bd_remover_usuario(f, user);
}

void BD::bd_remover_exemplarespecifico(const char* f, Exemplar* item){

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

void BD::bd_remover_exemplaresdoacervo(const char* f, Acervo* livro){

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

void BD::bd_remover_exemplaraluno(const char *f, int exemplarid){

    int codigoexemplar = exemplarid;
    string sql_comando = "Delete from AlunoExemplares where codigoexemplar="+to_string(codigoexemplar)+"; ";
    string alerta_erro = "ERRO AO REMOVER EXEMPLAR: "+to_string(codigoexemplar);
    
    executar_sql(f, sql_comando, alerta_erro);
}

bool BD::checkAcervo(const char* f, Acervo* livro){

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

bool BD::checkUsuario(const char* f, Perfil_usuario* user){

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

bool BD::checkExemplar(const char* f, Exemplar* item){

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
                cout << "ERRO: Ja existe um Exemplar com esse codigo especifico: "+to_string(codigoexemplarbd)+
                ", Codigo do Acervo corresp.: " << codigodoacervobd << "." << endl;
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

int BD::checkNumExemplares(const char* f, Acervo* livro){
    
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

void BD::updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoespecifico = item->getCodigoEspecifico();

    string sql_comando = "UPDATE Exemplares set emprestado="+to_string(umouzero)+" where codigoexemplar="+to_string(codigoespecifico)+";";
    string alerta_erro = "ERRO AO ATUALIZAR Emprestado em Exemplares: "+to_string(codigoespecifico);

    executar_sql(f, sql_comando, alerta_erro);

}

void BD::UpdateMultaExemplarAluno(const char* f, Exemplar* item){

    int multadoexemplar = item->calculaMulta();
    int iddoexemplar = item->getCodigoEspecifico();

    string sql_comando = "UPDATE AlunoExemplares set multa="+to_string(multadoexemplar)+" where codigoexemplar="+
    to_string(iddoexemplar)+"; ";

    string alerta_erro = "ERRO AO ATUALIZAR multa em AlunoExemplares: ";
    
    executar_sql(f, sql_comando, alerta_erro);

}