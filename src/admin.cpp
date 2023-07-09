#include "../include/admin.h"

Admin::Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
        bibdados.bd_inserir_admin(file, *this);
}

void Admin::adicionar_usuario(Perfil_usuario* perfil) {
    if(bibdados.checkUsuario(file, *perfil)) {
        throw id_ja_cadastrado_e();
    }

    _usuarios.push_back(perfil);
    bibdados.bd_inserir_tabela_usuarios(file, *perfil);

    if(perfil->get_papel_usuario()==BIBLIOTECARIO) {
        Bibliotecario *b = static_cast<Bibliotecario*>(perfil);
        bibdados.bd_inserir_bibliotecario(file, *b);
    }
    else {
        Aluno *a = static_cast<Aluno*>(perfil);
        bibdados.bd_inserir_aluno(file, *a);
    }

    // 
    // O proprio metodo do bd para inserir ja verifica se o id ja esta sendo utilizado.
    // if(papel==ALUNO) {
    //     Aluno a(id,email,senha,papel);
    //     //adiciona o aluno ao bd.
    //     bibdados.bd_inserir_aluno(file, a);
        
    // } else {
    //     //Construtor ainda não definido
    //     Bibliotecario b(id,email,senha,papel);
    //     //adiciona o bibliotecario ao bd.
    //     bibdados.bd_inserir_bibliotecario(file, b);

    // }
    
}


void Admin::deletar_usuario(Perfil_usuario *perfil) {
    // Checa se o id não é o do proprio admin, e depois se existe alguem com o id
    if(perfil->get_ID_perfil_usuario()==get_ID_perfil_usuario()) throw id_invalido_e();
    if(!bibdados.checkUsuario(file,*perfil)) throw perfil_nao_existe_e();

     // persistence: tentando montar essa logica aqui.
    sqlite3* bibdb;
    sqlite3_open(file, &bibdb);
    sqlite3_stmt* stmt;
    int id = perfil->get_ID_perfil_usuario();

    string sql_comando = "SELECT * FROM Usuarios where ID="+to_string(id)+"; ";

    sqlite3_prepare_v2(bibdb, sql_comando.c_str(), -1, &stmt, 0);
    int iduserbd = 0;
    const unsigned char* papeluserbd;
    int senhauserbd = 0;
      //20 784     104188
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        iduserbd = sqlite3_column_int(stmt, 0);
        senhauserbd = sqlite3_column_int(stmt, 2);
        papeluserbd = sqlite3_column_text(stmt, 3);
        if(iduserbd == id){
            // nao sei se a conversao abaixo possui algum problema
            if(papeluserbd == (const unsigned char*)"ALUNO") {
                Aluno alunocomoid(id,"",senhauserbd,ALUNO);
                bibdados.bd_remover_aluno_e_devolver_exemplares(file, alunocomoid);
                sqlite3_finalize(stmt);
                sqlite3_close(bibdb);
            }
            if(papeluserbd == (const unsigned char *)"BIBLIOTECARIO"){
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
            for(auto it = _usuarios.begin();it!=_usuarios.end();it++) {
                if((*it)->get_ID_perfil_usuario()==id) _usuarios.erase(it);
            }
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);
}

void Admin::consultar_Usuarios() {
    bibdados.bd_acessar_tabela_usuarios(file);
    cout << "\n";
}

Admin::~Admin() {}