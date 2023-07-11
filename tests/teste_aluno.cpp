#include <exception>

#include "doctest.h"
#include "aluno.h"


TEST_CASE("Testa o número de livros") {
	Aluno a("emaildoaluno@ufmg.br",123456);
	CHECK_EQ(a.get_n_exemplares(),0);

	Exemplar e("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	a.emprestar_livro(e);
	CHECK_EQ(a.get_n_exemplares(),1);
}

TEST_CASE("Testa o maximo de livros") {
	Aluno a("emaildoaluno@ufmg.br",123456);
	Exemplar e1("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	Exemplar e2("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	Exemplar e3("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	Exemplar e4("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	Exemplar e5("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	Exemplar e6("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);
	a.emprestar_livro(e1);
	a.emprestar_livro(e2);
	a.emprestar_livro(e3);
	a.emprestar_livro(e4);
	a.emprestar_livro(e5);
	CHECK_THROWS_AS(a.emprestar_livro(e6),std::exception);
}

TEST_CASE("Testa a devolucao com codigo invalido") {
	Aluno a("emaildoaluno@ufmg.br",123456);
	CHECK_THROWS_AS(a.devolver_livro(252443),std::exception);
}

TEST_CASE("Testa a devolucao de livros") {
	Aluno a("emaildoaluno@ufmg.br",123235);
	Exemplar e("James Stewart", 2000, "Calculo 1", 2, 3, 0, 10102030, 2);

	a.emprestar_livro(e);
	CHECK(a.get_n_exemplares()==1);
	a.devolver_livro(3);
	CHECK(a.get_n_exemplares()==0);
}