#include "../include/exemplar.h"
#include "../third_party/doctest.h"
#include <ctime>
#include <chrono>



TEST_CASE("Teste de cálculo da data de devolução") {
    // Cria um exemplar com data de aquisição fixa (04/07/2023)
    Exemplar exemplar("Autor", 2023, "Título", "Gênero", 1.0, false, 1);

      exemplar.setDataEmprestimo(20230704);
    // Calcula a data de devolução do exemplar
    int dataDevolucaoCalculada = exemplar.calculaDataDevolucaoSistema();

    // Verifica se a data de devolução calculada é igual à data de devolução esperada
    CHECK(dataDevolucaoCalculada == 20230804);
}

TEST_CASE("Exemplar Calcula Data Devolucao") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 1); //data aquisição 17/06/2023

    exemplar.setDataEmprestimo(20230617);

    REQUIRE(exemplar.calculaDataDevolucaoSistema() == 20230717); // data devolução 17/07/2023
}

TEST_CASE("Exemplar Calcula Data Devolucao") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 1); //data aquisição 17/06/2023

    exemplar.setDataEmprestimo(20240219);

    REQUIRE(exemplar.calculaDataDevolucaoSistema() == 20240319); // data devolução 19/03/2023 - passou
}

TEST_CASE("Exemplar Calcula Data Devolucao") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 1); //data aquisição 17/06/2023

  exemplar.setDataEmprestimo(20240218);

    REQUIRE(exemplar.calculaDataDevolucaoSistema() == 20240318); //
}



TEST_CASE("Exemplar Calcula Multa") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 1);
    // Data de aquisição: 09/06/2023
    // Data de devolução: 09/07/2023 (1 mês após aquisição)
    exemplar.setDataEmprestimo(20230609);

    SUBCASE("Sem atraso") {
        int multa = exemplar.calculaMulta();
        CHECK(multa == 0); //tem q ser 0
    }
}

TEST_CASE("Exemplar Calcula Multa") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 12345.67, false, 1);
    // Data de aquisição: 05/06/2023
    // Data de devolução: 08/07/2023 (1 mês e 4 dias após aquisição)
    exemplar.setDataEmprestimo(20230605);
    SUBCASE("Com 3 dias de atraso") {
             int multa = exemplar.calculaMulta();
    CHECK(multa == 4); //tem que ser 4
}
}
TEST_CASE("Exemplar - Teste do método getMulta - Com multa") {
    Exemplar exemplar("Autor", 2021, "Título", "Gênero", 1234, false,  1);
        exemplar.setDataEmprestimo(20230605);
        exemplar.calculaMulta();

        // Verificação do resultado
        CHECK(exemplar.getMulta() == 4); // Supondo que o valor da multa seja 4
    
}



















