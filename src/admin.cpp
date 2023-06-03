#include "admin.h"

Admin::Admin(unsigned int id, std::string email, int senha): Perfil_usuario(id, email, senha) {
}

void Admin::deletar_usuario(unsigned int id) {
    std::cout << "Usuario deletado." << std::endl;
}

void Admin::deletar_bibliotecario(unsigned int id) {
    std::cout << "Bibliotecario deletado." << std::endl;
}