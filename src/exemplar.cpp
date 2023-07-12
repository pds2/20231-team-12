#include "../include/exemplar.h"
#include <iostream>
#include <ctime>

Exemplar::Exemplar(int codigo, int codigoEspecifico, std::string autor, std::string titulo, int ano_publicacao, int genero)
    : Acervo(codigo, autor, titulo, ano_publicacao, genero), emprestado(0),
      codigoEspecifico(codigoEspecifico), dataEmprestimo(0)
{
    salva_exemplar_no_arquivo();
    bd_criar_tabela_exemplares(file);
    bd_inserir_tabela_exemplares(file, this);
}

Exemplar::~Exemplar() {}

int Exemplar::getCodigoEspecifico() const
{
    return this->codigoEspecifico;
}

int Exemplar::getDataEmprestimo() const
{
    return this->dataEmprestimo;
}
int Exemplar::calculaDataDevolucao()
{
    int dataDevolucao;
    std::tm aquisicao_time = {0};
    aquisicao_time.tm_mday = dataEmprestimo % 100;
    aquisicao_time.tm_mon = (dataEmprestimo / 100) % 100 - 1;
    aquisicao_time.tm_year = dataEmprestimo / 10000 - 1900;

    std::time_t aquisicao_timestamp = std::mktime(&aquisicao_time);

    // Adiciona um mês à data de aquisição
    std::tm devolucao_time = *std::localtime(&aquisicao_timestamp);
    devolucao_time.tm_mon += 1;

    std::time_t devolucao_timestamp = std::mktime(&devolucao_time);

    std::tm *devolucao_date = std::localtime(&devolucao_timestamp);

    dataDevolucao = (devolucao_date->tm_year + 1900) * 10000 + (devolucao_date->tm_mon + 1) * 100 + devolucao_date->tm_mday;

    return dataDevolucao;
}
int Exemplar::calculaMulta()
{
    int dataDevolucao;
    // pega a data de devolucao que devera estar em formato 18/06/2023 -> 18062023
    dataDevolucao = calculaDataDevolucao();

    int diaDevolucao, mesDevolucao, anoDevolucao;
    int diasAtraso = 0;
    int multa = 0;

    // utilizando biblioteca "ctime"
    std::time_t now = std::time(nullptr);         // obter a data e hora atuais
    std::tm *current_time = std::localtime(&now); // converter o valor de tempo em uma estrutura std::tm contendo informações sobre o ano, mês, dia.

    // extraindo os valores de dia atual, mes atual e ano atual da estrutura std::tm
    int diaAtual = current_time->tm_mday;
    int mesAtual = current_time->tm_mon + 1;     // retorna o mês atual, onde janeiro é representado por 0 e dezembro por 11, convertendo para 1 a 12(soma-se+1)
    int anoAtual = current_time->tm_year + 1900; // 1900 - convenção C Library

    int dataAtual = diaAtual + mesAtual * 100 + anoAtual * 10000; // operação q combina o ano, mês e dia em formato de data numérica 17/06/23 -> 20230617

    diaDevolucao = dataDevolucao % 100;
    mesDevolucao = (dataDevolucao / 100) % 100;
    anoDevolucao = dataDevolucao / 10000;

    if (anoAtual > anoDevolucao || (anoAtual == anoDevolucao && mesAtual > mesDevolucao) || (anoAtual == anoDevolucao && mesAtual == mesDevolucao && diaAtual > diaDevolucao))
    {
        // Calcula a diferença em dias apenas se a data atual for posterior à data de devolução
        std::tm devolucao_time = {0};
        devolucao_time.tm_mday = diaDevolucao;
        devolucao_time.tm_mon = mesDevolucao - 1;
        devolucao_time.tm_year = anoDevolucao - 1900;

        /*std::mktime() é uma função da biblioteca <ctime> que converte uma estrutura std::tm em um valor de
        tempo (std::time_t). Nesse caso, estamos convertendo a estrutura devolucao_time que contém a data de
        devolução para um valor de tempo.*/
        std::time_t devolucao_timestamp = std::mktime(&devolucao_time);

        /*Aqui, estamos criando uma estrutura std::tm chamada atual_time e inicializando todos os seus campos como zero.*/
        std::tm atual_time = {0};
        atual_time.tm_mday = diaAtual;
        atual_time.tm_mon = mesAtual - 1;
        atual_time.tm_year = anoAtual - 1900;

        /*Da mesma forma que fizemos para a data de devolução, estamos convertendo a estrutura atual_time, que
        contém a data atual, em um valor de tempo std::time_t.*/
        std::time_t atual_timestamp = std::mktime(&atual_time);

        // Calcula a diferença em segundos entre as datas
        std::time_t diff_seconds = std::difftime(atual_timestamp, devolucao_timestamp);
        /*std::difftime() é uma função da biblioteca <ctime> que calcula a diferença de tempo entre dois valores de tempo (std::time_t) em segundos.*/

        // Converte a diferença em segundos para dias
        diasAtraso = static_cast<int>(diff_seconds) / (60 * 60 * 24);
        /*Estamos convertendo a diferença de tempo em segundos (diff_seconds) para dias, dividindo-a por 60 segundos
         (para obter minutos), depois por 60 minutos (para obter horas) e finalmente por 24 horas (para obter dias).
         O static_cast<int> é usado para converter o valor resultante em um número inteiro, pois estamos interessados
         apenas nos dias inteiros de atraso.*/
    }

    if (diasAtraso > 0)
    {
        multa = diasAtraso * 1;
        std::cout << "Multa de: R$ " << multa << std::endl;
    }
    else
    {
        std::cout << "Nenhuma multa!" << std::endl;
        ;
    }

    UpdateMultaExemplarAluno(file, this);
    return multa;
}

int Exemplar::salva_exemplar_no_arquivo()
{
    std::ofstream exemplar_out;
    exemplar_out.open("exemplares.csv", std::ios_base::app);
    if (!exemplar_out)
    {
        std::cout << "arquivo nao existe" << std::endl;
        return 0;
    }
    else
    {
        exemplar_out << this->get_codigo() << "," << this->codigoEspecifico << this->get_titulo() << "," << this->get_autor() << ","
                     << this->get_ano_publicacao() << "," << this->get_genero() << this->emprestado << this->dataEmprestimo;
        exemplar_out.close();
        return 1;
    }
}

//PERSISTENCE:

void Exemplar::executar_sql(const char* f, string comandosql, string avisoerro){
    
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

void Exemplar::bd_criar_tabela_exemplares(const char* f){

    string sql_comando = "CREATE TABLE IF NOT EXISTS Exemplares("
    "autor TEXT NOT NULL,"
    "anopublicacao INTEGER NOT NULL,"
    "titulo TEXT NOT NULL,"
    "genero INT NOT NULL,"
    "codigo INTEGER NOT NULL,"
    "codigoexemplar TEXT NOT NULL,"
    "emprestado INT NOT NULL)";

    string alerta_erro =  "ERRO AO CRIAR A TABELA ACERVOS: ";

    executar_sql(f, sql_comando, alerta_erro);
}

void Exemplar::bd_inserir_tabela_exemplares(const char* f, Exemplar* item){

    bool check = checkExemplar(f, item);
    if(check==(0||false)){
        string autor, titulo;
        autor = item->get_autor(); 
        int anopub = item->get_ano_publicacao(); 
        titulo = item->get_titulo(); 
        int genero = item->get_genero();
        int codigo = item->get_codigo();
        int codigo_exemplar = item->getCodigoEspecifico();
        int emprestado = 0;

        string sql_comando = "INSERT INTO Exemplares VALUES('"+autor+"',"+to_string(anopub)+",'"+titulo+"',"+to_string(genero)+","+
        to_string(codigo)+","+to_string(codigo_exemplar)+","+to_string(emprestado)+");";

        string alerta_erro = "ERRO AO INSERIR EM EXEMPLARES: ";

        executar_sql(f, sql_comando, alerta_erro);
    }
}

void Exemplar::bd_acessar_tabela_exemplares(const char* f){

    bool check = checkTabelaExiste(f,"Exemplares");

    if(check==(1||true)){

        sqlite3* bibdb;
        sqlite3_open(f, & bibdb);
        sqlite3_stmt* stmt;

        string sql_consulta = "SELECT * FROM Exemplares;";

        sqlite3_prepare_v2(bibdb, sql_consulta.c_str(), -1, &stmt, 0);

        const unsigned char* autor;
        const unsigned char* titulo;
        const unsigned char* codigo_exemplar;
        int emprestado ;
        int anopub, codigo, genero;
        int numexemplares = 0;

        while(sqlite3_step(stmt)!=SQLITE_DONE){

            autor = sqlite3_column_text(stmt, 0);
            anopub = sqlite3_column_int(stmt, 1);
            titulo = sqlite3_column_text(stmt, 2);
            genero = sqlite3_column_int(stmt, 3);
            codigo = sqlite3_column_int(stmt, 4);
            codigo_exemplar = sqlite3_column_text(stmt, 5);
            emprestado = sqlite3_column_int(stmt, 6);
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

void Exemplar::bd_destruir_tabela_exemplares(const char* f){

    string sql_comando = "Drop Table Exemplares; ";
    string alerta_erro = "ERRO AO DESTRUIR TABELA EXEMPLARES: ";
    executar_sql(f, sql_comando, alerta_erro);

}

void Exemplar::bd_remover_exemplarespecifico(const char* f, Exemplar* item){

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

bool Exemplar::checkExemplar(const char* f, Exemplar* item){

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
                // cout << "ERRO: Ja existe um Exemplar com esse codigo especifico: "+to_string(codigoexemplarbd)+
                // ", Codigo do Acervo corresp.: " << codigodoacervobd << "." << endl;
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

bool Exemplar::checkTabelaExiste(const char*f, string nome_tabela){

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

void Exemplar::updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero){
    sqlite3* bibdb;
    sqlite3_open(f, &bibdb);

    int codigoespecifico = item->getCodigoEspecifico();

    string sql_comando = "UPDATE Exemplares set emprestado="+to_string(umouzero)+" where codigoexemplar="+to_string(codigoespecifico)+";";
    string alerta_erro = "ERRO AO ATUALIZAR Emprestado em Exemplares: "+to_string(codigoespecifico);

    executar_sql(f, sql_comando, alerta_erro);

}

void Exemplar::UpdateMultaExemplarAluno(const char* f, Exemplar* item){

    int multadoexemplar = item->calculaMulta();
    int iddoexemplar = item->getCodigoEspecifico();

    string sql_comando = "UPDATE AlunosExemplares set multa="+to_string(multadoexemplar)+" where codigoexemplar="+
    to_string(iddoexemplar)+"; ";

    string alerta_erro = "ERRO AO ATUALIZAR multa em AlunosExemplares: ";
    
    executar_sql(f, sql_comando, alerta_erro);
}