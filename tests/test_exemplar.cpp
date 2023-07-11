#include "../include/exemplar.h"
#include "../third_party/doctest.h"
#include <ctime>
#include <chrono>

#include "doctest.h"
#include "../include/exemplar.h"



TEST_CASE("Teste de cálculo da data de devolução") {
    // Cria um exemplar com data de aquisição fixa (04/07/2023)
    Exemplar exemplar("Autor", 2023, "Título", "Gênero", 172, false, 12412023);

      exemplar.setDataEmprestimo(20230704);
    // Calcula a data de devolução do exemplar
    int dataDevolucaoCalculada = exemplar.calculaDataDevolucaoSistema();

    // Verifica se a data de devolução calculada é igual à data de devolução esperada
    CHECK(dataDevolucaoCalculada == 20230804);
}


TEST_CASE("Exemplar Calcula Data Devolucao") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 694, false, 34572021); 

    exemplar.setDataEmprestimo(20230617); //data aquisição 17/06/2023

    CHECK(exemplar.calculaDataDevolucaoSistema() == 20230717); // data devolução 17/07/2023
}


TEST_CASE("Exemplar Calcula Data Devolucao") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 234, false, 12792021); 

    exemplar.setDataEmprestimo(20240219);//data aquisição 19/02/2024

    CHECK(exemplar.calculaDataDevolucaoSistema() == 20240319); // data devolução 19/03/2023 - passou
}


TEST_CASE("Exemplar Calcula Data Devolucao") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 845, false, 14352021); //data aquisição 17/06/2023

  exemplar.setDataEmprestimo(20240218); //data aquisição 18/02/2024

    CHECK(exemplar.calculaDataDevolucaoSistema() == 20240318); 
}


//Teste passou, dia 08/07/2023 deve ficar em comentário, pois ele vai mudando conforme a data
//logo abaixo há um igual porem pegando os dias passados desde o dia do teste como se ele tivesse aumentando a multa ainda a mais no assertion a cada dia
/*
TEST_CASE("Exemplar - Teste do método getMulta - Com multa") {
    Exemplar exemplar("Autor", 2021, "Título", "Gênero", 123, false,  76592021);
    // Data de aquisição: 05/06/2023
    // Data de devolução: 08/07/2023 (1 mês e 3 dias após aquisição)
        exemplar.setDataEmprestimo(20230605);
        exemplar.calculaMulta();

        // Verificação do resultado
        CHECK(exemplar.getMulta() == 3); // Supondo que o valor da multa seja 3
} 
*/


//Pegando os dias passados desde o dia do teste como se ele tivesse aumentando a multa ainda a mais no assertion a cada dia
TEST_CASE("Exemplar - Teste do método getMulta e método Calcula Multa - Com multa de 3 reais")
{
    Exemplar exemplar("Autor", 2021, "Título", "Gênero", 124, false, 14782021);
    // Data de aquisição: 05/06/2023
    // Data de devolução: 08/07/2023 (1 mês e 4 dias após aquisição)
    exemplar.setDataEmprestimo(20230605);
    exemplar.calculaMulta();

    // Calcular o número de dias passados desde o dia 8 de julho de 2023 até a data atual
    std::time_t dataAtual;
    std::time(&dataAtual);

    std::tm dataFutura = {0};
    dataFutura.tm_year = 123; // Ano: 2023 - tm_year representa o número de anos desde 1900
    dataFutura.tm_mon = 6;   // Mês: 7 - julho,  pois vai de  0 - 11 meses ao invés de 1 a 12
    dataFutura.tm_mday = 8;  // Dia: 8

    //métodos da biblioteca c.time
    std::time_t dataFuturaTimestamp = std::mktime(&dataFutura);
    std::time_t duracaoTimestamp = dataAtual - dataFuturaTimestamp;

    int diasPassados = duracaoTimestamp / (60 * 60 * 24); // Conversão para dias

    // Verificação do resultado
    int multaEsperada = 3 + diasPassados; // Supondo que o valor da multa seja 4 inicialmente
    CHECK(exemplar.getMulta() == multaEsperada);
}

//Teste passou, dia 08/07/2023 deve ficar em comentário, pois ele vai mudando conforme a data e vai gerar multa
/*
TEST_CASE("Exemplar Calcula Multa - test do getMulta - Sem multa") {
    Exemplar exemplar("Autor", 2021, "Titulo", "Genero", 235, false, 13452021);
    // Data de aquisição: 09/06/2023
    // Data de devolução: 09/07/2023 (1 mês após aquisição)
    exemplar.setDataEmprestimo(20230609);

    SUBCASE("Sem atraso") {
        int multa = exemplar.getMulta();
        CHECK(multa == 0); 
    }
}
*/

TEST_CASE("Teste de métodos getters e construtor") {
    Exemplar exemplar("Kiera Cass", 2008, "A seleção", "Romance", 012, true, 32472008);

    // Verifica se os valores fornecidos no construtor são armazenados corretamente
    CHECK(exemplar.getAutor() == "Kiera Cass");
    CHECK(exemplar.getAnoPublicacao() == 2008);
    CHECK(exemplar.getTitulo() == "A seleção");
    CHECK(exemplar.getGenero() == "Romance");
    CHECK(exemplar.getCodigo() == 012);
    CHECK(exemplar.isEmprestado() == true);
    CHECK(exemplar.getCodigoEspecifico() == 32472008);
}

















