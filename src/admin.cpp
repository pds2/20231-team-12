#include "admin.h"

Admin::Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
        std::cout << "Admim criado" << std::endl;
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