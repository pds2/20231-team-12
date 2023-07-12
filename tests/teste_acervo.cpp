#include "doctest.h"
#include "acervo.h"

#include <exception>

TEST_CASE("Testa o construtor do acervo") {
    CHECK_NOTHROW(Acervo(2,"autor","titulo",2023,5));
    CHECK_NOTHROW(Acervo(123413,"algum autor","titulo do livro",2030,1254243));
}

TEST_CASE("Testa o get_codigo") {
    Acervo a1(10,"autor1","titulo1",2020,1);
    Acervo a2(20,"autor2","titulo2",2021,2);
    Acervo a3(30,"autor3","titulo3",2022,3);
    Acervo a4(40,"autor4","titulo4",2023,4);

    CHECK(a1.get_codigo()==10);
    CHECK(a2.get_codigo()==20);
    CHECK(a3.get_codigo()==30);
    CHECK(a4.get_codigo()==40);
}

TEST_CASE("Testa o get_autor") {
    Acervo a1(10,"autor1","titulo1",2020,1);
    Acervo a2(20,"autor2","titulo2",2021,2);
    Acervo a3(30,"autor3","titulo3",2022,3);
    Acervo a4(40,"autor4","titulo4",2023,4);
    
    CHECK(a1.get_autor()=="autor1");
    CHECK(a2.get_autor()=="autor2");
    CHECK(a3.get_autor()=="autor3");
    CHECK(a4.get_autor()=="autor4");
}

TEST_CASE("Testa o get_titulo") {
    Acervo a1(10,"autor1","titulo1",2020,1);
    Acervo a2(20,"autor2","titulo2",2021,2);
    Acervo a3(30,"autor3","titulo3",2022,3);
    Acervo a4(40,"autor4","titulo4",2023,4);
    
    CHECK(a1.get_titulo()=="titulo1");
    CHECK(a2.get_titulo()=="titulo2");
    CHECK(a3.get_titulo()=="titulo3");
    CHECK(a4.get_titulo()=="titulo4");
}

TEST_CASE("Testa o get_ano_publicacao") {
    Acervo a1(10,"autor1","titulo1",2020,1);
    Acervo a2(20,"autor2","titulo2",2021,2);
    Acervo a3(30,"autor3","titulo3",2022,3);
    Acervo a4(40,"autor4","titulo4",2023,4);
    
    CHECK(a1.get_ano_publicacao()==2020);
    CHECK(a2.get_ano_publicacao()==2021);
    CHECK(a3.get_ano_publicacao()==2022);
    CHECK(a4.get_ano_publicacao()==2023);
}

TEST_CASE("Testa o get_genero") {
    Acervo a1(10,"autor1","titulo1",2020,1);
    Acervo a2(20,"autor2","titulo2",2021,2);
    Acervo a3(30,"autor3","titulo3",2022,3);
    Acervo a4(40,"autor4","titulo4",2023,4);
    
    CHECK(a1.get_genero()==1);
    CHECK(a2.get_genero()==2);
    CHECK(a3.get_genero()==3);
    CHECK(a4.get_genero()==4);
}

TEST_CASE("Testa o operador <") {
    Acervo a1(10,"autor1","titulo1",2020,1);
    Acervo a2(20,"autor2","titulo2",2021,2);
    
    CHECK(a2<a1);
}