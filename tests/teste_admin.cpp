#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <exception>

#include "doctest.h"
#include "admin.h"

TEST_CASE("Testa a adicao de um admin") {
    Admin a(5, "emaildoadmin@ufmg.br", 123456, ADMIN);
    CHECK_THROWS_AS(a.adicionar_usuario(10,"algumemail",123456,ADMIN),exception);
}

TEST_CASE("Testa o a tentativa de se deletar") {
    Admin a(5, "emaildoadmin@ufmg.br", 123456, ADMIN);
    CHECK_THROWS_AS(a.deletar_usuario(5), exception);
}