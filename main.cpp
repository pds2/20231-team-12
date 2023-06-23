#include <iostream>
#include <string>
#include <vector>

#include "include/bancodedados.h"

using namespace std;


int main(){

    sqlite3* bibdb;
    sqlite3_stmt* stmt;

    const char* file = "biblioteca.db";

    BD dados = BD();

    dados.bd_criar_tabela_acervos(file);
    dados.bd_criar_tabela_usuarios(file);
    dados.bd_criar_tabela_exemplares(file);

    Acervo calc("James Stewart",2021,"Calculo 1","Matematica",2411);
    Acervo md("Kenneth H. Rosen", 1995,"Matematica Discreta e suas Aplicacoes","Matematica",6109);

    dados.bd_inserir_tabela_acervos(file, calc);
    dados.bd_inserir_tabela_acervos(file, md);

    dados.bd_acessar_tebela_acervos(file);


    return 0;

}



