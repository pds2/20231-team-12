#include <iostream>
#include <string>
#include <vector>

#include "include/bancodedados.h"

using namespace std;


int main(){

    const char* file = "biblioteca.db";

    BD dados;

    dados.bd_criar_tabela_acervos(file);
    dados.bd_criar_tabela_usuarios(file);
    dados.bd_criar_tabela_exemplares(file);

    // Acervo calc("James Stewart",2021,"Calculo 1","Matematica",2411);
    // Acervo md("Kenneth H. Rosen", 1995,"Matematica Discreta e suas Aplicacoes","Matematica",6109);

    // dados.bd_inserir_tabela_acervos(file, calc);
    // dados.bd_inserir_tabela_acervos(file, md);

    // Perfil_usuario tha(12,"thaissa@example.com", 123456);

    // dados.bd_inserir_tabela_usuarios(file, tha);


    // Exemplar md1("Kenneth H. Rosen", 1995, "Matematica Discreta e suas Aplicacoes", "Matematica", 6109, true, 10012021, 347609, 20032021);

    // dados.bd_inserir_tabela_exemplares(file, md1);

    // dados.bd_destruir_tabela_acervos(file);

    // dados.bd_remover_acervo(file, calc);

    // dados.bd_remover_usuario(file,tha);

    // dados.bd_remover_exemplar(file, md1);

    // dados.bd_remover_acervo(file, md);

    // Acervo clc("James Stewart",2021,"Calculo 1","Matematica",2411);
    // cout << dados.checkAcervo(file, clc) << endl;

    // Acervo hpc("Deitel",1992,"C++ como progrmar","Programacao", 5474);

    // dados.bd_inserir_tabela_acervos(file, hpc);

    // Perfil_usuario lagosta(14,"lagostinha@simple",123456);
    // cout << dados.checkUsuario(file, lagosta);

    // dados.bd_inserir_tabela_usuarios(file, lagosta);
    
    // cout << dados.checkNumExemplares(file, md);

    // Admin leila(10,"leilacabelereira",789012);
    // dados.bd_inserir_admin(file, leila);
    
    // Aluno carls(8,"CarlsFarls",923540);
    // dados.bd_inserir_aluno(file, carls);

    // Bibliotecario tia(5,"tiadabiblioteca",654532);
    // dados.bd_inserir_bibliotecario(tia);

    //deixar fixo aqui
    // cout << "\n";
    // dados.bd_acessar_tebela_acervos(file);
    // dados.bd_acessar_tabela_usuarios(file);
    // dados.bd_acessar_tabela_exemplares(file);


    return 0;

}



