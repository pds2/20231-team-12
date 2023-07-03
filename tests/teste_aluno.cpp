#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <exception>

#include "doctest.h"
#include "aluno.h"


TEST_CASE("Testa o número de livros") {
	Aluno a(4, "emaildoaluno@ufmg.br",123456,ALUNO);
	CHECK_EQ(a.get_n_exemplares(),0);

	Exemplar e("James Stewart", 2000, "Calculo 1", "Matematica", 3, 0, 10102010, 2, 10112010);
	a.emprestar_livro(e);
	CHECK_EQ(a.get_n_exemplares(),1);
}

TEST_CASE("Testa o emprestimo com multa") {
	Aluno a(4, "emaildoaluno@ufmg.br",123456,ALUNO);
	Exemplar e1("James Stewart", 2000, "Calculo 1", "Matematica", 3, 0, 10102010, 2, 10112010);
	Exemplar e2("James Stewart", 2001, "Calculo 2", "Matematica", 4, 0, 10102010, 2, 10112010);
	a.emprestar_livro(e1);
	CHECK_THROWS_AS(a.emprestar_livro(e2),exception);
}

TEST_CASE("Testa o maximo de livros") {
	Aluno a(4, "emaildoaluno@ufmg.br",123456,ALUNO);
	Exemplar e1("James Stewart", 2000, "Calculo 1", "Matematica", 3, 0, 10102010, 2, 10112090);
	Exemplar e2("James Stewart", 2001, "Calculo 2", "Matematica", 4, 0, 10102010, 2, 10112090);
	Exemplar e3("James Stewart", 2000, "Calculo 3", "Matematica", 3, 0, 10102010, 2, 10112090);
	Exemplar e4("James Stewart", 2001, "Calculo 4", "Matematica", 4, 0, 10102010, 2, 10112090);
	Exemplar e5("James Stewart", 2000, "Calculo 5", "Matematica", 3, 0, 10102010, 2, 10112090);
	Exemplar e6("James Stewart", 2001, "Calculo 6", "Matematica", 4, 0, 10102010, 2, 10112090);
	a.emprestar_livro(e1);
	a.emprestar_livro(e2);
	a.emprestar_livro(e3);
	a.emprestar_livro(e4);
	a.emprestar_livro(e5);
	CHECK_THROWS_AS(a.emprestar_livro(e6),exception);
}

TEST_CASE("Testa a devolucao de livros") {
	Aluno a(4, "emaildoaluno@ufmg.br",123456,ALUNO);
	CHECK_THROWS_AS(a.devolver_livro(2),exception);
	
	Exemplar e("James Stewart", 2000, "Calculo 1", "Matematica", 3, 0, 10102010, 2, 10112090);
	a.emprestar_livro(e);
	a.devolver_livro(2);
	CHECK_EQ(a.get_n_exemplares(),0);
}