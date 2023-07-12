#include <exception>

#include "doctest.h"
#include "aluno.h"
#include "admin.h"

// será utilizado a classe admin para excluir o aluno criado nos testes 

TEST_CASE("Testa o construtor do aluno") {
	CHECK_NOTHROW(Aluno("emailEMAILemailEMAIL",3141599999));
	CHECK_NOTHROW(Aluno("EMAILemailEMAILemail",987123465));
}

TEST_CASE("Testa o empréstimo de livros") {
	Exemplar e(1234293,129348,"AUTORrautor","titulo....-423",10423,4363);
	Aluno a("emaildoadmin@@!@",102501234);
	CHECK_NOTHROW(a.emprestar_livro(&e));
}

TEST_CASE("Testa o número de livros") {
	Aluno a("emaildoadmin@@@",100123234);
	Exemplar e(12342293,1289348,"AUTOrautor","titulo&...-423",104623,24363);

	CHECK(a.get_n_exemplares()==0);
	
	a.emprestar_livro(&e);
	CHECK(a.get_n_exemplares()==1);
	
	a.devolver_livro(e.get_codigo());
	CHECK(a.get_n_exemplares()==0);
}

TEST_CASE("Testa o metodo consultar_acervo") {
	Aluno a("emaildoadmb@@@",100237234);
	Aluno aa("emailsenhasenha",194823256);

	CHECK_NOTHROW(a.consultar_acervo("1h24cfhn623c23874c632"));
	CHECK_NOTHROW(aa.consultar_acervo("we08d90vf8"));
}