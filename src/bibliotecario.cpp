#include "../include/bibliotecario.hpp"
#include "../include/bancodedados.h"

Papel_do_usuario Bibliotecario::set_papel_usuario()
{
    return BIBLIOTECARIO;
}

BD bibdados;

void Bibliotecario::adicionar_acervo(Acervo acervo_novo)
{
    acervo_novo.bd_inserir_tabela_acervos(file, acervo_novo);
}

void Bibliotecario::adicionar_exemplar(Exemplar exemplar_novo)
{
    bibdados.bd_inserir_tabela_exemplares(file, &exemplar_novo);
}

void Bibliotecario::remover_acervo(Acervo acervo_deletado)
{
    bibdados.bd_remover_acervo(file, &acervo_deletado);
}

void Bibliotecario::remover_exemplar(Exemplar exemplar_deletado)
{
    bibdados.bd_remover_exemplarespecifico(file, &exemplar_deletado);
}

void Bibliotecario::emprestimo_de_exemplar(Exemplar exemplar_emprestado)
{
    bibdados.updateExemplarEmprestado(file, &exemplar_emprestado, 1);
}

void Bibliotecario::devolucao_de_exemplar(Exemplar exemplar_devolvido)
{
    bibdados.updateExemplarEmprestado(file, &exemplar_devolvido, 0);
}

void Bibliotecario::consulta_geral_acervos(Exemplar especifico){

    bibdados.bd_acessar_tebela_acervos(file);
    bibdados.checkNumExemplares(file, &especifico);

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


void Bibliotecario::bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user){

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


void Bibliotecario::bd_inserir_aluno(const char* f, Aluno* aluno){

    bd_inserir_tabela_usuarios(f, aluno);

    int alunoid = aluno->get_ID_perfil_usuario();
    string papel = "ALUNO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(alunoid)+"; ";

    string alerta_erro = "ERRO AO INSERIR aluno EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);

}


void Bibliotecario::bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item){

    int alunoid = aluno->get_ID_perfil_usuario();
    int codigoexemplar = item->getCodigoEspecifico();
    int multa = item->calculaMulta();

    string sql_comando = "INSERT INTO AlunoExemplares VALUES("+to_string(alunoid)+","+to_string(codigoexemplar)+","+
    to_string(multa)+"); ";

    string alerta_erro = "ERRO AO INSERIR EM ALUNOEXEMPLARES: ";

    executar_sql(f, sql_comando, alerta_erro);
}



void Bibliotecario::bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno){

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

void Bibliotecario::bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario){

    bd_inserir_tabela_usuarios(f, bibliotecario);

    int bibliotecarioid = bibliotecario->get_ID_perfil_usuario();
    string papel = "BIBLIOTECARIO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(bibliotecarioid)+";";

    string alerta_erro = "ERRO AO INSERIR bibliotecario EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Bibliotecario::bd_remover_exemplaraluno(const char *f, int exemplarid){

    int codigoexemplar = exemplarid;
    string sql_comando = "Delete from AlunoExemplares where codigoexemplar="+to_string(codigoexemplar)+"; ";
    string alerta_erro = "ERRO AO REMOVER EXEMPLAR: "+to_string(codigoexemplar);
    
    executar_sql(f, sql_comando, alerta_erro);
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

    string sql_comando = "UPDATE AlunoExemplares set multa="+to_string(multadoexemplar)+" where codigoexemplar="+
    to_string(iddoexemplar)+"; ";

    string alerta_erro = "ERRO AO ATUALIZAR multa em AlunoExemplares: ";
    
    executar_sql(f, sql_comando, alerta_erro);

}