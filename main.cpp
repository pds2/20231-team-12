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

    Perfil_usuario tha(12,"thaissa@example.com", 123456);

    dados.bd_inserir_tabela_usuarios(file, tha);

    dados.bd_acessar_tabela_usuarios(file);

    Exemplar md1("Kenneth H. Rosen", 1995, "Matematica Discreta e suas Aplicacoes", "Matematica", 6109, true, 10012021, 347609, 20032021);

    dados.bd_inserir_tabela_exemplares(file, md1);

    dados.bd_acessar_tabela_exemplares(file);




    return 0;

}


