#include "doctest.h"
#include "acervo.h"

TEST_CASE("Acervo - Teste do método getAutor") {
    // Criação de um objeto Acervo para realização do teste
    Acervo acervo("Paula Pimenta", 2022, "Título Teste", "Gênero Teste", 123);

    // Verificação do resultado
    CHECK(acervo.getAutor() == "Paula Pimenta");
}

TEST_CASE("Acervo - Teste do método getTitulo") {
    // Criação de um objeto Acervo para realização do teste
    Acervo acervo("Paula Pimenta", 2022, "fazendo meu filme", "Gênero Teste", 123);

    // Verificação do resultado
    CHECK(acervo.getTitulo() == "fazendo meu filme");
}

TEST_CASE("Acervo - Teste do método getGenero") {
    // Criação de um objeto Acervo para realização do teste
    Acervo acervo("Paula Pimenta", 2022, "fazendo meu filme", "Romance", 123);

    // Verificação do resultado
    CHECK(acervo.getGenero() == "Romance");
}

TEST_CASE("Acervo - Teste do método getAnoPublicacao") {
    // Criação de um objeto Acervo para realização do teste
    Acervo acervo("Paula Pimenta", 2012, "fazendo meu filme", "Romance", 123);

    // Verificação do resultado
    CHECK(acervo.getAnoPublicacao() == 2012);
}
