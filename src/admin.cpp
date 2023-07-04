#include "admin.h"

Admin::Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
        std::cout << "Admin criado." << std::endl;
        bibdados.bd_inserir_admin(file, *this);
}

void Admin::adicionar_usuario(unsigned int id, std::string email, int senha, Papel_do_usuario papel) {
    if(papel == ADMIN) throw papel_invalido_e();
    /*
    Verifica se o email e id são novos ou já estão cadastrados com outro usuario. Se estiver,
    lançar alguma das exceções: email_ja_cadastrado_e e id_ja_cadastrado_e
    for(todos os usuarios do bd) {
        if(id==id do usuario) throw id_ja_cadastrado_e();
        if(email==email do usuario) throw email_ja_cadastrado_e();
    }
    */

    // O proprio metodo do bd para inserir ja verifica se o id ja esta sendo utilizado.
    if(papel==ALUNO) {
        Aluno a(id,email,senha,papel);
        //adiciona o aluno ao bd.
        bibdados.bd_inserir_aluno(file, a);
        
    } else {
        //Construtor ainda não definido
        Bibliotecario b(id,email,senha,papel);
        //adiciona o bibliotecario ao bd.
        bibdados.bd_inserir_bibliotecario(file, b);

    }
    
}


void Admin::deletar_usuario (unsigned int id) {
    //verifica se o id não é do próprio admin, e depois se existe algum usuario com esse id
    if(get_ID_perfil_usuario()==id) throw id_invalido_e();
    bool b = true;

    // for(*todos os usuario do bd*) if(usuario.get_ID_perfil_usuario()==id) b = false;
    if(b) throw id_nao_existe_e();


    /*for(*todos os usuario do bd*) {
        if(id do usuario == id) {
            if(usuario for aluno) devolver todos os livros que estão com o aluno
            deletar o usuario
        }
    */

   //Persistence: Checando se o id eh do admin:
   
   bool checkadmin = bibdados.checkUsuario(file, *this);
   if(checkadmin == (1||true)) throw id_invalido_e();
   else{
    // persistence: tentando montar essa logica aqui.
        sqlite3* bibdb;
        sqlite3_open(file, &bibdb);
        sqlite3_stmt* stmt;
        
        string sql_comando = "SELECT * FROM Usuarios where ID="+to_string(id)+"; ";

        sqlite3_prepare_v2(bibdb, sql_comando.c_str(), -1, &stmt, 0);
        int iduserbd = 0;
        const unsigned char* papeluserbd;
        int senhauserbd = 0;
        
        while(sqlite3_step(stmt)!=SQLITE_DONE){
            iduserbd = sqlite3_column_int(stmt, 0);
            senhauserbd = sqlite3_column_int(stmt, 2);
            papeluserbd = sqlite3_column_text(stmt, 3);

            if(iduserbd == id){
                if(papeluserbd == "ALUNO"){
                    Aluno alunocomoid(id,"",senhauserbd,ALUNO);
                    bibdados.bd_remover_aluno_e_devolver_exemplares(file, alunocomoid);
                    sqlite3_finalize(stmt);
                    sqlite3_close(bibdb);

                }
                else if(papeluserbd == "BIBLIOTECARIO"){
                    string sql_comando = "Delete from Usuarios where ID="+to_string(id)+"; ";
                    char* msgerr;
                    int resp = 0;

                    resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
                    if(resp!=SQLITE_OK){
                        cerr << "ERRO AO REMOVER USUARIO: " << msgerr << endl;
                    }
                    sqlite3_finalize(stmt);
                    sqlite3_free(msgerr);
                    sqlite3_close(bibdb);

                }
            }
        }
        sqlite3_finalize(stmt);
        sqlite3_close(bibdb);
   }
}

void Admin::consultar_Usuarios(){
    bibdados.bd_acessar_tabela_usuarios(file);
    cout << "\n";
}

Admin::~Admin() {}
