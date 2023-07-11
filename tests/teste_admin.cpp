#include <exception>

#include "doctest.h"
#include "admin.h"

TEST_CASE("Testa o construtor") {
    // não importa se o último parametro é true ou false, só precisa dele pra 
    // não usar o bd
    CHECK_NOTHROW(Admin("emaildoadmin@ufmg.br",123345));
    CHECK_NOTHROW(Admin("email",123429));
}

TEST_CASE("Testa a adicao e exclusao de usuarios") {
    Admin adm("email@ufmg.br",923454);
    Aluno b("email",82374);
    CHECK_NOTHROW(adm.adicionar_usuario((int)ALUNO,b.get_email_perfil_usuario(),
        b.get_senha_perfil_usuario()));
    CHECK_NOTHROW(adm.deletar_usuario(b.get_ID_perfil_usuario()));
}

TEST_CASE("Testa a tentativa de se deletar") {
    Admin a("emaildoadmin@ufmg.br", 1232342456);
    CHECK_THROWS_AS(a.deletar_usuario(a.get_ID_perfil_usuario()), std::exception);
}
