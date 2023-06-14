#include <iostream>
#include <string>


#include "sqlite/sqlite3.h"

using namespace std;

int main(){

    /*Abrindo uma conexão com o banco de dados(bibdb), criando um banco de dados(biblioteca.db),
      stm eh uma instrucao preparada.
    */
    sqlite3* bibdb;
    sqlite3_stmt* stmt;
    sqlite3_open("biblioteca.db", &bibdb);

    /*Criando uma tabela para o acervo.
      a variável resp eh utilizada para armazenar o retorno da funcao.
      o ponteiro err eh referenciado no quinto argumento da funcao exec para retornar mensagem de erro se necess.
      caso a tabela nao possa ser criada retornamos um erro.
    */
    char* err;
    int resp = sqlite3_exec(bibdb,"CREATE TABLE IF NOT EXISTS acervos(autor TEXT,anopublicacao INT,titulo text,genero text,codigo INT);",NULL,NULL, &err);
    if(resp!=SQLITE_OK){
        cout << "ERRO AO CRIAR A TABELA ACERVOS: " << err << endl;
    }

    /*tentando destruir a tabela acervos. PERIGO!!! FUNCIONA! */
    /*
    resp = sqlite3_exec(bibdb,"DROP TABLE acervos;",NULL,NULL, &err);
    if(resp!=SQLITE_OK){
        cout<<"ERRO AO DESTRUIR A TABELA ACERVOS: " << err << endl;
    }
    */

   




    return 0;
}