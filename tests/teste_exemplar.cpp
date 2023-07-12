#include "exemplar.h"
#include "doctest.h"

#include <exception>

TEST_CASE("Testa o construtor") {
    CHECK_NOTHROW(Exemplar(89754302,812424,"autoraaaautoraut","livrolivrolivro,livro2",19999,52365));
    CHECK_NOTHROW(Exemplar(8975402,87652424,"autor???oraut","livroliv,,,livro2",124349999,5237545));
    CHECK_NOTHROW(Exemplar(124112,1354231,"!!!*$@","20395svd",234921234,4112544));
}

TEST_CASE("Testa os getters") {
    Exemplar e(89754002,812424,"autoraaaautoraut","livrolivrolivro,livro2",19999,5235);

    CHECK(e.getCodigoEspecifico()==812424);
    CHECK(e.getDataEmprestimo()==0);
    CHECK(e.get_ano_publicacao()==19999);
    CHECK(e.get_autor()=="autoraaaautoraut");
    CHECK(e.get_titulo()=="livrolivrolivro,livro2");
    CHECK(e.get_codigo()==89754002);
    CHECK(e.get_genero()==5235);
    CHECK(e.isEmprestado()==false);
}