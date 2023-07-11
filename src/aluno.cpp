#include "../include/aluno.h"

#include <iostream>
#include <iomanip>

Aluno::Aluno(std::string email, int senha) : Perfil_usuario(email, senha)
{
    this->_papel = ALUNO;
    salvar_aluno_no_arquivo();
    bd_criar_tabela_usuarios(file);
    bd_criar_tabela_exemplaresaluno(file);
    bd_inserir_aluno(file, this);
}

Aluno::~Aluno()
{
    for (auto it : livros_com_aluno)
    {
        delete it;
    }
    livros_com_aluno.clear();
    this->BDauxiliar("Persistence20231");
    bd_remover_usuario(file, this, "Persistence20231");
}

/*
void Aluno::livros_emprestados()
{
    if (exemplares.size() == 0)
        std::cout << "O aluno nao possui nenhum livro." << std::endl;
    else
        std::cout << "Livro(s) emprestado(s) para o aluno:" << std::endl;
    for (auto l : exemplares)
        std::cout << l.getTitulo() << ", escrito por " << l.getAutor() << std::endl; // imprimir os dados dos livros
}
*/

int Aluno::get_n_exemplares()
{
    return this->livros_com_aluno.size();
}

void Aluno::emprestar_livro(Exemplar *livro)
{
    if (this->livros_com_aluno.size() > 5)
        throw ja_possui_mutos_livros_e();
    for (auto l : livros_com_aluno)
        if (l->calculaMulta() != 0)
        {
            throw aluno_com_multa_e();
        }
    livros_com_aluno.push_back(livro);
    updateExemplarEmprestado(file, livro, 1);
    bd_inserir_alunoexemplar(file, this, livro);
}

void Aluno::devolver_livro(int codigo)
{
    bool p = true;
    for (auto l : this->livros_com_aluno)
        if (l->get_codigo() == codigo)
            p = false;
    if (p)
    {
        throw nao_possui_esse_livro_e();
    }

    int i = 0;
    for (auto l : livros_com_aluno)
    {
        if (l->get_codigo() == codigo){
            livros_com_aluno.erase(livros_com_aluno.begin() + i);
            updateExemplarEmprestado(file, l, 0);
            bd_remover_exemplaraluno(file, l->getCodigoEspecifico());
        }
        i++;
    }
}

void Aluno::consultar_acervo(std::string titulo) // pro aluno so retorna codigo, titulo e autor, e # exemplares disponiveis
{
    bd_acessar_acervoportitulo(file, titulo);

    std::ifstream arquivo_acervo("acervo.csv");
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

                std::cout << "Acervo encontrado:\n";
                std::cout << "Código: " << codigo_int << '\n';
                std::cout << "Título: " << titulo << '\n';
                std::cout << "Autor: " << autor << '\n';
            }
        }
    }

    arquivo_acervo.close();
}

/*
void Aluno::consultar_multa(int codigo)
{
    bool p = true;
    for (auto l : exemplares)
        if (l.getCodigoEspecifico() == codigo)
            p = false;
    if (p)
        throw nao_possui_esse_livro_e();
    double r;
    for (auto l : exemplares)
        if (l.getCodigoEspecifico() == codigo)
            r = l.calculaMulta();

    if (r == 0)
        std::cout << "Este livro não possui multa." << std::endl;
    else
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "A multa deste livro é de R$" << r << "." << std::endl;
    }
}



//SO ESSA AQUI
void Aluno::consultar_multa_total()
{
    double total = 0;
    std::cout << std::fixed << std::setprecision(2);
    for (auto l : this->livros_com_aluno)
    {
        double m = l->calculaMulta();
        total += m;
        if (m != 0)
            std::cout << "A multa de " << l->getTitulo() << " é de R$" << m << "." << std::endl;
    }
    if (total != 0)
        std::cout << "O total da(s) multa(s) de todos os livros é R$" << total << "." << std::endl;
    else
        std::cout << "Não há nenhuma multa no nome do aluno." << std::endl;
}
*/

int Aluno::salvar_aluno_no_arquivo()
{
    std::ofstream aluno_out;
    aluno_out.open("usuarios.csv", std::ios_base::app);
    if (!aluno_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        aluno_out << this->get_ID_perfil_usuario() << ","
                  << this->get_email_perfil_usuario() << "," << this->get_senha_perfil_usuario() << "," << this->get_senha_perfil_usuario() << std::endl;

        aluno_out.close();
        return 1;
    }
}

//devolucao de todos os exemplares.
void Aluno::BDauxiliar(string codigosecreto){
    if(codigosecreto=="Persistence20231"){
        for(auto exemplaremprestado : livros_com_aluno){
            updateExemplarEmprestado(file, exemplaremprestado, 0);
            cout << "O Exemplar: "<< exemplaremprestado->getCodigoEspecifico() <<" foi devolvido."<<endl;
        }
    }
}

//PERSISTENCE

void Aluno::executar_sql(const char* f, string comandosql, string avisoerro){
    
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

void Aluno::bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user){

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

void Aluno::bd_inserir_aluno(const char* f, Aluno* aluno){

    bd_inserir_tabela_usuarios(f, aluno);

    int alunoid = aluno->get_ID_perfil_usuario();
    string papel = "ALUNO";

    string sql_comando = "UPDATE Usuarios set papel='"+papel+"' where ID="+to_string(alunoid)+"; ";

    string alerta_erro = "ERRO AO INSERIR aluno EM Usuarios: ";

    executar_sql(f, sql_comando, alerta_erro);

}

void Aluno::bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item){

    int alunoid = aluno->get_ID_perfil_usuario();
    int codigoexemplar = item->getCodigoEspecifico();
    int multa = item->calculaMulta();

    string sql_comando = "INSERT INTO AlunoExemplares VALUES("+to_string(alunoid)+","+to_string(codigoexemplar)+","+
    to_string(multa)+"); ";

    string alerta_erro = "ERRO AO INSERIR EM ALUNOEXEMPLARES: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Aluno::bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno){

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

void Aluno::bd_acessar_acervoportitulo(const char* f, std::string titulo){ 

    sqlite3* bibdados;
    sqlite3_open(f, &bibdados);
    sqlite3_stmt* stmt;
    sqlite3_stmt* stmt2;

    string sql_comando = "SELECT * FROM Acervos where titulo='"+titulo+"';";

    sqlite3_prepare_v2(bibdados, sql_comando.c_str(),-1,&stmt,0);

    int codigo, codigo2;
    const unsigned char* autor;
    const unsigned char* titulo2;
    int numexemplares = 0;

    while(sqlite3_step(stmt)!=SQLITE_DONE){
        codigo = sqlite3_column_int(stmt, 4);
        
        string sql_comando = "SELECT * FROM Exemplares where codigo="+to_string(codigo)+" and emprestado=0;";
        sqlite3_prepare_v2(bibdados, sql_comando.c_str(),-1,&stmt2,0);

        while(sqlite3_step(stmt2)!=SQLITE_DONE){

            autor = sqlite3_column_text(stmt, 0);
            titulo2 = sqlite3_column_text(stmt, 2);
            codigo2 = sqlite3_column_int(stmt, 4);
            numexemplares++;

            cout << "Exemplar "+to_string(numexemplares)+": " << endl;
            cout << "autor: " << autor << endl;
            cout << "titulo: " << titulo << endl;
            cout << "codigo: " << codigo2 << endl;
            cout << "\n";
        }
        
        sqlite3_finalize(stmt);
        sqlite3_finalize(stmt2);
        sqlite3_close(bibdados);
    }
}

void Aluno::bd_remover_exemplaraluno(const char *f, int exemplarid){

    int codigoexemplar = exemplarid;
    string sql_comando = "Delete from AlunoExemplares where codigoexemplar="+to_string(codigoexemplar)+"; ";
    string alerta_erro = "ERRO AO REMOVER EXEMPLAR: "+to_string(codigoexemplar);
    
    executar_sql(f, sql_comando, alerta_erro);
}

void Aluno::bd_remover_usuario(const char* f, Perfil_usuario* user, string codigosecreto){
    if(codigosecreto == "Persistence20231"){
        int iduser = user->get_ID_perfil_usuario();
        string sql_comando = "Delete from Usuarios where ID="+to_string(iduser)+"; ";
        string alerta_erro = "ERRO AO REMOVER USUARIO: "+to_string(iduser)+" ";

        executar_sql(f, sql_comando, alerta_erro);
    }
}

bool Aluno::checkUsuarioid(const char* f, Perfil_usuario* user){

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
            cout << "ERRO: Usuario ja cadastrado com id: "+to_string(idigual)+", email: '" << emailigual << "'." << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);

    return false;
}

bool Aluno::checkUsuarioemail(const char* f, Perfil_usuario* user){
    
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);
    sqlite3_stmt* stmt;

    string email = user->get_email_perfil_usuario();
    int iduser = user->get_ID_perfil_usuario();

    string sql_consulta = "SELECT * FROM Usuarios where email='"+email+"'; ";

    sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);
    int idigual = 0;
    const unsigned char* emailigual;

    while(sqlite3_step(stmt)!=SQLITE_DONE){
        idigual = sqlite3_column_int(stmt, 0);
        emailigual = sqlite3_column_text(stmt, 1);

        if(emailigual!=0){
            cout << "ERRO: Usuario ja cadastrado com o email: '"+email+"', id: " << to_string(idigual) << "." << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(bibdb);
            return true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bibdb);
    return false;

}

bool Aluno::checkTabelaExiste(const char*f, string nome_tabela){

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

void Aluno::updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoespecifico = item->getCodigoEspecifico();

    string sql_comando = "UPDATE Exemplares set emprestado="+to_string(umouzero)+" where codigoexemplar="+to_string(codigoespecifico)+";";
    string alerta_erro = "ERRO AO ATUALIZAR Emprestado em Exemplares: "+to_string(codigoespecifico);

    executar_sql(f, sql_comando, alerta_erro);

}

void Aluno::UpdateMultaExemplarAluno(const char* f, Exemplar* item){

    int multadoexemplar = item->calculaMulta();
    int iddoexemplar = item->getCodigoEspecifico();

    string sql_comando = "UPDATE AlunoExemplares set multa="+to_string(multadoexemplar)+" where codigoexemplar="+
    to_string(iddoexemplar)+"; ";

    string alerta_erro = "ERRO AO ATUALIZAR multa em AlunoExemplares: ";
    
    executar_sql(f, sql_comando, alerta_erro);

}
