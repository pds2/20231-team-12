#include <exception>

#include "doctest.h"
#include "admin.h"

TEST_CASE("Testa o construtor") {
    CHECK_NOTHROW(Admin("algumemail@gmail.com",124235));
    CHECK_NOTHROW(Admin("loginadmin@ufmg.br",215953));
}

TEST_CASE("Testa os getters") {
    Admin a("email1",1), b("email2",2);
    CHECK(a.get_papel_usuario()==ADMIN);
    CHECK(b.get_papel_usuario()==ADMIN);
    CHECK(a.get_senha_perfil_usuario()==1);
    CHECK(b.get_email_perfil_usuario()=="email2");
}

TEST_CASE("Testa a adicao de um admin/numero inválido") {
    Admin a("emaildoadmin@ufmg.br", 123456);
    CHECK_THROWS_AS(a.adicionar_usuario(1,"algumemail",123456),std::exception);
    CHECK_THROWS_AS(a.adicionar_usuario(10,"emailemail",126434),std::exception);
    CHECK_THROWS_AS(a.adicionar_usuario(396023,".",14),std::exception);
}

TEST_CASE("Testa o metodo deletar_usuario") {
    Admin a("123",456);
    CHECK_NOTHROW(a.adicionar_usuario(2,"u1",1));
    CHECK_NOTHROW(a.deletar_usuario("u1"));
}

TEST_CASE("Testa o a tentativa de se deletar") {
    Admin a("emaildoadmin@ufmg.br", 123456);
    CHECK_THROWS_AS(a.deletar_usuario("emaildoadmin@ufmg.br"), std::exception);
}

TEST_CASE("Testa o metodo consultar_acervo(nao faz nada para admin)") {
    Admin adm("email",8523);
    CHECK_NOTHROW(adm.consultar_acervo(""));
    CHECK_NOTHROW(adm.consultar_acervo("string"));
}