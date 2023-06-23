#include "admin.h"

Admin::Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
        std::cout << "Admim criado" << std::endl;
}

void Admin::adicionar_usuario(unsigned int id, std::string email, int senha, Papel_do_usuario papel) {
    if(papel == ADMIN) throw papel_invalido_e();
    /*
    Verifica se o email e id são novos ou já estão cadastrados com outro usuario. Se estiver,
    lançar alguma das exceções: email_ja_cadastrado_e e id_ja_cadastrado_e
    */
    if(papel==ALUNO) {
        Aluno a(id,email,senha,papel);
        //adiciona o aluno ao bd.
    } else {
        //Construtor ainda não definito
        //Bibliotecario b(id,email,senha,papel);
        //adiciona o bibliotecario ao bd.
    }
    
}

void Admin::deletar_aluno(unsigned int id) {
    if(get_ID_perfil_usuario()==id) throw id_invalido_e();
    bool b = true;
    //for( *verifica os usuarios* ) if(usuario.get_ID_perfil_usuario()==id) b = false;
    if(b) throw id_nao_existe_e();
    
    std::cout << "Aluno deletado." << std::endl;
}

void Admin::deletar_bibliotecario(unsigned int id) {
    if(get_ID_perfil_usuario()==id) throw id_invalido_e();
    bool b = true;
    //for( *verifica os usuarios* ) if(usuario.get_ID_perfil_usuario()==id) b = false;
    if(b) throw id_nao_existe_e();
    
    std::cout << "Bibliotecario deletado." << std::endl;
}
Admin::~Admin() {
}