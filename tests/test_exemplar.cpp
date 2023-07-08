// #include "../include/exemplar.h"

// #include "../third_party/doctest.h"

// #include "exemplar.h"

// #include "doctest.h"

#include "../include/exemplar.h"
#include "../third_party/doctest.h"

TEST_CASE("Teste de cálculo da data de devolução")
{
    // Cria um exemplar com data de aquisição fixa (04/07/2023)
    Exemplar exemplar("Autor", 2023, "Título", "Gênero", 1.0, false, 20230704, 1, 0);

    // Calcula a data de devolução do exemplar
    int dataDevolucaoCalculada = exemplar.calculaDataDevolucao();

    // Verifica se a data de devolução calculada é igual à data de devolução esperada
    CHECK(dataDevolucaoCalculada == 20230804);
}

TEST_CASE("Exemplar Calcula Data Devolucao")
{
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 20230617, 1, 0); // data aquisição 17/06/2023

    REQUIRE(exemplar.calculaDataDevolucao() == 20230717); // data devolução 17/07/2023
}

TEST_CASE("Exemplar Calcula Data Devolucao")
{
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 20240219, 1, 0); // data aquisição 17/06/2023

    REQUIRE(exemplar.calculaDataDevolucao() == 20240319); // data devolução 19/03/2023 - passou
}

TEST_CASE("Exemplar Calcula Data Devolucao")
{
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 20240218, 1, 0); // data aquisição 17/06/2023

    REQUIRE(exemplar.calculaDataDevolucao() == 20240319); // data devolução 18/03/2024 - deu errado e era para dar errado - passou
}

// deu errado - verificar
TEST_CASE("Exemplar Calcula Multa com 3 dia de atraso")
{
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 20230617, 1, 0);

    CHECK(exemplar.calculaMulta() == 3);
}

/*
g++ -std=c++20 test_exemplar.cpp exemplar.cpp -o test_exemplar -Ilibs
./test_exemplar?

g++ -I../third_party test_exemplar.cpp -o test_exemplar

g++ -I../third_party ../tests/test_exemplar.cpp -o test_exemplar
*/
/*
g++ test_exemplar.cpp testes.cpp -o meu_programa
*/