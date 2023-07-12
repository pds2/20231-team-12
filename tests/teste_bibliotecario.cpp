#include "doctest.h"
#include "bibliotecario.hpp"
#include "aluno.h"
#include "exemplar.h"

#include <exception>

TEST_CASE("Testa o construtor") {
    CHECK_NOTHROW(Bibliotecario("eaaf831290rc82190",912349035));
    CHECK_NOTHROW(Bibliotecario("-235rt324vg",359028323));
}

TEST_CASE("Testa o consultar_acervo") {
    Bibliotecario b1("958340ft34v",9230456834);
    Bibliotecario b2("sdoa753 8v",13954928);

    CHECK_NOTHROW(b1.consultar_acervo("453vnfvb"));
    CHECK_NOTHROW(b2.consultar_acervo("198c75  asd5 "));
}

TEST_CASE("Testa o adicionar_acervo") {
    Bibliotecario b1("95834h0f134v",923456839);

    CHECK_NOTHROW(b1.adicionar_acervo(11354,"stringstring","titulotitulo",2058,1234));
    CHECK_NOTHROW(b1.adicionar_acervo(11354341,"strin16gstring","titulot2itulo",20568,132234));
}

TEST_CASE("Testa o empresimo de exemplar") {
    Bibliotecario b("958s34h0f134v",92356839);
    Exemplar e(3548654,53856423,"algumautorlivro","titulodolivroo",2345,1243);
    Aluno a("emaildoalunoalunoaluno",12894739);

    CHECK_NOTHROW(b.emprestimo_de_exemplar(&e,a));
}