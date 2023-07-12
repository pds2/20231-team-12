#include <iostream>
#include <string>
#include <vector>

#include "include/bibliotecario.hpp"
#include "include/acervo.h"
#include "include/admin.h"
#include "include/aluno.h"
#include "include/perfil_usuario.hpp"
#include "include/exemplar.h"

using namespace std;


// void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero);
// void executar_sql(const char* f, string comandosql, string avisoerro);

int main()
{
    // Bibliotecario bib1 = Bibliotecario("er", 123);

    // std::cout << bib1.get_ID_perfil_usuario();


    Acervo a1(12,"Deitel","Como Programar",1992,1);
    Acervo a2(4,"Ferreira","Xfile",2005,3);
    Acervo a3(78,"Nicolas","Como ser inteligente",2015,2);
    Acervo a4(24,"Paulinha","A razao dos vicios",2002,2);
    Acervo a5(14,"Palmirinha","Arroz Doce",1986,3);
    Acervo a6(12,"e","a",1020,0);

    Exemplar e1(12,3,"Deitel","Como Programar",1992,1);
    Exemplar e2(4,5,"Ferreira","Xfile",2005,3);
    Exemplar e3(12,2,"Deitel","Como Programar",1992,1);
    Exemplar e4(78,1,"Nicolas","Como ser inteligente",2015,2);
    Exemplar e5(78,17,"Nicolas","Como ser inteligente",2015,2);
    Exemplar e6(14,0,"Palmirinha","Arroz Doce",1986,3);

    Admin ad1("paulo@email.com",3478);
    Admin ad2("guilherme@email.com",9090);
    Admin ad3("laura@gmail.com",7104);

    Aluno al1("sarahaluna@email.com",3227);
    Aluno al2("barataaluna@email.com",7865);
    Aluno al3("caraaluna@email.com",6524);
    Aluno al4("gilbertogilaluno@email.com",7056);

    Bibliotecario b1("snrnivea@email.com",8654);
    Bibliotecario b2("tiarose@email.com",1102);
    Bibliotecario b3("niltondboa@email.com",6203);

    al1.consultar_acervo("Como Programar");
    b1.emprestimo_de_exemplar(&e1,al1);

    // const char* file = "biblioteca.db";
    // updateExemplarEmprestado(file, &e1, 1);
    return 0;
}

// void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero){
//     sqlite3* bibdb;
//     sqlite3_open(f, &bibdb);

//     int codigoespecifico = item->getCodigoEspecifico();

//     string sql_comando = "UPDATE Exemplares set emprestado = "+to_string(umouzero)+" where codigoexemplar = "+to_string(codigoespecifico)+";";
//     string alerta_erro = "ERRO AO ATUALIZAR Emprestado em Exemplares: "+to_string(codigoespecifico);

//     executar_sql(f, sql_comando, alerta_erro);

// }

// void executar_sql(const char* f, string comandosql, string avisoerro){
    
//     //criando uma conexao com o banco de dados.
//     sqlite3* bibdb;
    
//     //abrindo o banco de dados.
//     sqlite3_open(f, &bibdb);

//     //comando para criar uma tabela, sintaxe sql.
//     string sql_comando = comandosql;
//     string alerta_erro = avisoerro;

//     //para armazenar mensagens de erro e retorno da funcao, repsectivamente.
//     char* msgerr;
//     int resp = 0;

//     //funcao que cria a tabela.
//     resp = sqlite3_exec(bibdb, sql_comando.c_str(), NULL, NULL, &msgerr);
//     if(resp!=SQLITE_OK){
//         cerr << alerta_erro << msgerr << endl;
//     }
    
//     //liberando memoria.
//     sqlite3_free(msgerr);    
//     sqlite3_close(bibdb);  
// }