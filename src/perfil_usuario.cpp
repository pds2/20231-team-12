#include "../include/perfil_usuario.hpp"

Perfil_usuario::Perfil_usuario()
{
    _ID_perfil_usuario = 99999;
    _email_perfil_usuario = ("VAZIO");
    _senha_pefil_usuario = 99999;
    _papel = ADMIN;
}

Perfil_usuario::Perfil_usuario(unsigned int ID, std::string email, int senha, Papel_do_usuario papel)
{
    _ID_perfil_usuario = ID;
    _email_perfil_usuario = email;
    _senha_pefil_usuario = senha;
    _papel = papel;
}

Papel_do_usuario Perfil_usuario::get_papel_usuario()
{
    return _papel;
}

unsigned int Perfil_usuario::get_ID_perfil_usuario()
{
    return _ID_perfil_usuario;
}

std::string Perfil_usuario::get_email_perfil_usuario()
{
    return _email_perfil_usuario;
}

int Perfil_usuario::get_senha_perfil_usuario()
{
    return _senha_pefil_usuario;
}
