#include "../include/admin.h"

Admin::Admin(std::string email, int senha) : Perfil_usuario(email, senha)
{
    this->_papel = ADMIN;
    std::cout << "Admin criado." << std::endl;
    bd_criar_tabela_usuarios(file);
    bd_inserir_admin(file, this);

}

void Admin::adicionar_usuario(int tipo_de_user, std::string email, int senha)
{
    /*
    if (papel == ADMIN)
        throw papel_invalido_e();

    Verifica se o email e id são novos ou já estão cadastrados com outro usuario. Se estiver,
    lançar alguma das exceções: email_ja_cadastrado_e e id_ja_cadastrado_e
    for(todos os usuarios do bd) {
        if(id==id do usuario) throw id_ja_cadastrado_e();
        if(email==email do usuario) throw email_ja_cadastrado_e();
    }

    if (papel == ALUNO)
    {
        Aluno a(id, email, senha, papel);
        // adiciona o aluno ao bd.
    }
    else
    {
        // Construtor ainda não definito
        // Bibliotecario b(id,email,senha,papel);
        // adiciona o bibliotecario ao bd.
    }
    */
    if (tipo_de_user = ALUNO)
    {
        Aluno *novo_aluno = new Aluno(email, senha);
        novo_aluno->salvar_aluno_no_arquivo();
        bd_inserir_aluno(file, novo_aluno);
        delete novo_aluno;
    }
    else if (tipo_de_user = BIBLIOTECARIO)
    {
        Bibliotecario *novo_bibliotecario = new Bibliotecario(email, senha);
        novo_bibliotecario->salvar_bibl_no_arquivo();
        bd_inserir_bibliotecario(file, novo_bibliotecario);
        delete novo_bibliotecario;
    }
}

void Admin::deletar_usuario(std::string email)
{
    // verifica se o id não é do próprio admin, e depois se existe algum usuario com esse id
    if (this->get_email_perfil_usuario() == email)
    {
        throw id_invalido_e();
    }

    bd_remover_usuarioporemail(file, email);

    std::ifstream arquivo_usuarios("usuarios.csv");
    std::ofstream arquivo_atualizado("usuarios_temp.csv");
    std::string linha;

    while (getline(arquivo_usuarios, linha))
    {

        // bool b = true;
        //  for(*todos os usuario do bd*) if(usuario.get_ID_perfil_usuario()==id) b = false;
        // if (b)
        //    throw id_nao_existe_e();

        /*for(*todos os usuario do bd*) {
            if(id do usuario == id) {
                if(usuario for aluno) devolver todos os livros que estão com o aluno
                deletar o usuario
            }
        }*/

        std::ifstream arquivo_usuarios("usuarios.csv");
        std::ofstream arquivo_atualizado("usuarios_temp.csv");
        std::string linha;

        while (getline(arquivo_usuarios, linha))
        {
            std::istringstream iss(linha);
            std::string campo;
            bool email_encontrado = false;

            while (getline(iss, campo, ','))
            {
                if (campo == email)
                {
                    email_encontrado = true;
                    break;
                }
            }

            if (!email_encontrado)
            {
                arquivo_atualizado << linha << '\n';
            }
        }

        arquivo_usuarios.close();
        arquivo_atualizado.close();

        remove("usuarios.csv");
        rename("usuarios_temp.csv", "usuarios.csv");
    }
}

void Admin::consultar_acervo(std::string titulo)
{
    // nao pode acontecer nada aqui, admin nao liga pra livro
}

Admin::~Admin()
{
}

//PERSISTENCE

void Admin::executar_sql(const char* f, string comandosql, string avisoerro){
    
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

void Admin::bd_inserir_admin(const char* f, Admin* adm){

    bd_inserir_tabela_usuarios(f, adm);

    int admid = adm->get_ID_perfil_usuario();
    string papel = "ADMIN";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(admid)+"; ";

    string alerta_erro = "ERRO AO INSERIR Admin EM Usuarios: ";
    
    executar_sql(f, sql_comando, alerta_erro);
}


void Admin::bd_inserir_aluno(const char* f, Aluno* aluno){

    bd_inserir_tabela_usuarios(f, aluno);

    int alunoid = aluno->get_ID_perfil_usuario();
    string papel = "ALUNO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(alunoid)+"; ";

    string alerta_erro = "ERRO AO INSERIR aluno EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);

}

void Admin::bd_inserir_bibliotecario(const char* f, Bibliotecario* bibliotecario){

    bd_inserir_tabela_usuarios(f, bibliotecario);

    int bibliotecarioid = bibliotecario->get_ID_perfil_usuario();
    string papel = "BIBLIOTECARIO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(bibliotecarioid)+";";

    string alerta_erro = "ERRO AO INSERIR bibliotecario EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);
}


void Admin::bd_acessar_tabela_usuarios(const char* f){

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

void Admin::bd_acessar_acervoportitulo(const char* f, std::string titulo)
{
    sqlite3* bibdados;
    sqlite3_open(f, &bibdados);
    sqlite3_stmt* stmt;
    sqlite3_stmt* stmt2;

    string sql_comando = "SELECT * FROM Acervos where titulo='"+titulo+"';";

    sqlite3_prepare_v2(bibdados, sql_comando.c_str(),-1,&stmt,0);

    int anopub, codigo, codigo2;
    const unsigned char* autor;
    const unsigned char* titulo2;
    const unsigned char* genero;
    int numexemplares = 0;
    const unsigned char* codigo_exemplar;
    const unsigned char* emprestado;

    while(sqlite3_step(stmt)!=SQLITE_DONE){
        codigo = sqlite3_column_int(stmt, 4);
        
        string sql_comando = "SELECT * FROM Exemplares where codigo="+to_string(codigo)+";";
        sqlite3_prepare_v2(bibdados, sql_comando.c_str(),-1,&stmt2,0);

        while(sqlite3_step(stmt2)!=SQLITE_DONE){

            autor = sqlite3_column_text(stmt, 0);
            anopub = sqlite3_column_int(stmt, 1);
            titulo2 = sqlite3_column_text(stmt, 2);
            genero = sqlite3_column_text(stmt, 3);
            codigo2 = sqlite3_column_int(stmt, 4);
            codigo_exemplar = sqlite3_column_text(stmt, 5);
            emprestado = sqlite3_column_text(stmt, 6);
            numexemplares++;

            cout << "Exemplar "+to_string(numexemplares)+": " << endl;
            cout << "autor: " << autor << endl;
            cout << "ano de publicacao: " << anopub << endl;
            cout << "titulo: " << titulo << endl;
            cout << "genero: " << genero << endl;
            cout << "codigo: " << codigo2 << endl;
            cout << "codigo do exemplar: " << codigo_exemplar << endl; 
            cout << "emprestado: " << emprestado << endl;
            cout << "\n";
        }
        
        sqlite3_finalize(stmt2);
    }
        sqlite3_finalize(stmt);
        sqlite3_close(bibdados);
}

void Admin::bd_remover_usuario(const char* f, Perfil_usuario* user){

    int iduser = user->get_ID_perfil_usuario();
    string sql_comando = "Delete from Usuarios where ID="+to_string(iduser)+"; ";
    string alerta_erro = "ERRO AO REMOVER USUARIO: "+to_string(iduser)+" ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Admin::bd_remover_usuarioporid(const char* f, int id){

    string sql_comando = "Delete from Usuarios where ID="+to_string(id)+"; ";
    string alerta_erro = "ERRO AO REMOVER USUARIO: "+to_string(id)+" ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Admin::bd_remover_usuarioporemail(const char* f, string email){
    
    bool check = checkTabelaExiste(f, "Usuarios");

    if(check==(1||true)){
        sqlite3* bibdb;
        sqlite3_open(f, &bibdb);
        sqlite3_stmt* stmt;

        string sql_comando = "SELECT * FROM Usuarios where email='"+email+"';";

        sqlite3_prepare_v2(bibdb, sql_comando.c_str(), -1, &stmt, 0);

        int id;
        const unsigned char* email2;
        int senha, papelint;
        const unsigned char* papel;
        int numusuarios = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){
            
            id = sqlite3_column_int(stmt, 0);
            email2 = sqlite3_column_text(stmt, 1);
            senha = sqlite3_column_int(stmt, 2);
            papel = sqlite3_column_text(stmt, 3);
            papelint = sqlite3_column_int(stmt, 3);

            if(papel == "ALUNO" || papelint == 2){
                Aluno a1(email,senha);
                bd_remover_aluno_e_devolver_exemplares(file, &a1);
            }

        }

        sqlite3_free(stmt);
        sqlite3_close(bibdb);

        string sql_comando = "Delete from Usuarios where email="+email+"; ";
        string alerta_erro = "ERRO AO REMOVER USUARIO: "+email+" ";

        executar_sql(f, sql_comando, alerta_erro); 
    }
    else{
        cerr << "ERRO AO ACESSAR TABELA INEXISTENTE: Usuarios" << endl;
    }
}

void Admin::bd_remover_aluno_e_devolver_exemplares(const char* f, Aluno *user){

    user->BDauxiliar("Persistence20231");
    bd_remover_usuario(f, user);
}

bool Admin::checkUsuario(const char* f, Perfil_usuario* user){

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

bool Admin::checkTabelaExiste(const char*f, string nome_tabela){

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

void Admin::updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoespecifico = item->getCodigoEspecifico();

    string sql_comando = "UPDATE Exemplares set emprestado="+to_string(umouzero)+" where codigoexemplar="+to_string(codigoespecifico)+";";
    string alerta_erro = "ERRO AO ATUALIZAR Emprestado em Exemplares: "+to_string(codigoespecifico);

    executar_sql(f, sql_comando, alerta_erro);

}

void Admin::UpdateMultaExemplarAluno(const char* f, Exemplar* item){

    int multadoexemplar = item->calculaMulta();
    int iddoexemplar = item->getCodigoEspecifico();

    string sql_comando = "UPDATE AlunoExemplares set multa="+to_string(multadoexemplar)+" where codigoexemplar="+
    to_string(iddoexemplar)+"; ";

    string alerta_erro = "ERRO AO ATUALIZAR multa em AlunoExemplares: ";
    
    executar_sql(f, sql_comando, alerta_erro);
}