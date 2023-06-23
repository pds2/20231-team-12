#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS

#include "../sqlite/sqlite3.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
#include "exemplar.h"

class BD{
    public:
    
    //Construtor apenas para instanciar.
    BD();
    
    //metodos que ciam as tabelas. funcionam da mesma forma. a repeticao eh necessaria.
    static int bd_criar_tabela_acervos(const char* f);
    static int bd_criar_tabela_usuarios(const char* f);
    static int bd_criar_tabela_exemplares(const char* f);

    //metodos para inserir acervos.
    static int bd_inserir_tabela_acervos(const char* f, Acervo livro);
    static int bd_inserir_tabela_usuarios(const char* f, Perfil_usuario user);
    static int bd_inserir_tabela_exemplares(const char* f, Exemplar item);

    //metodos para acessar/selecionar acervos.
    static int bd_acessar_tebela_acervos(const char* f);
    static int bd_acessar_tabela_usuarios(const char* f);
    static int bd_acessar_tabela_exemplares(const char* f);





};

#endif