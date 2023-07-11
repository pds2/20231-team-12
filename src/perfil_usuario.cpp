#include "../include/perfil_usuario.hpp"

int Perfil_usuario::CONTADOR_ID_perfil_usuario = 0;

Perfil_usuario::Perfil_usuario()
{
    _ID_perfil_usuario = 99999;
    _email_perfil_usuario = ("VAZIO");
    _senha_pefil_usuario = 99999;
    _papel = ALUNO;
}

Perfil_usuario::Perfil_usuario(std::string email, int senha) : _email_perfil_usuario(email), _senha_pefil_usuario(senha)
{
    _ID_perfil_usuario = CONTADOR_ID_perfil_usuario;
    CONTADOR_ID_perfil_usuario++;
}

Papel_do_usuario Perfil_usuario::get_papel_usuario()
{
    return this->_papel;
}

unsigned int Perfil_usuario::get_ID_perfil_usuario()
{
    return this->_ID_perfil_usuario;
}

std::string Perfil_usuario::get_email_perfil_usuario()
{
    return this->_email_perfil_usuario;
}

int Perfil_usuario::get_senha_perfil_usuario()
{
    return this->_senha_pefil_usuario;
}
