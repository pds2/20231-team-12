#include "admin.h"

Admin::Admin(unsigned int id, std::string email, int senha, Papel_do_usuario papel):
    Perfil_usuario(id, email, senha, papel) {
        std::cout << "Admim criado" << std::endl;
}

Papel_do_usuario Admin::get_papel_usuario() {
    return ADMIN;
}

void Admin::deletar_usuario(unsigned int id) {
    std::cout << "Usuario deletado." << std::endl;
}

void Admin::deletar_bibliotecario(unsigned int id) {
    std::cout << "Bibliotecario deletado." << std::endl;
}