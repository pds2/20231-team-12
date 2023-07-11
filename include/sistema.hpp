#ifndef SISTEMA_H
#define SISTEMA_H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/admin.h"
#include "../include/acervo.h"
#include "../include/aluno.h"
#include "../include/bibliotecario.hpp"
#include "../include/perfil_usuario.hpp"
#include "../include/exemplar.h"

// precisa ter um mapa dos livros, id sendo o acervo, dai os exemplares tem uma ordem dentro (1,2,3) pode so ser por int e dai tem um contador
//  dentro da classe que sabe quantos foram criados e so deleta o especifico, nunca quebra a ordem, vai deletar so o id ali no csv

// outro mapa dos usuarios, passa o email deles e um vetor de todos

class Sistema
{
private:
    std::map<Acervo, std::vector<Exemplar>> biblioteca;
    std::map<std::string, std::vector<Perfil_usuario *>> usuarios;

public:
    Sistema();
    ~Sistema();

    void carregar_acervos();
    void carregar_usuarios();
    int tela_cadastro();
    int tela_login();
    void tela_aluno(int);
    void tela_bibliotecario(int);
    void tela_admin(int);
    void inicia_sistema();
};
#endif
