#ifndef ACERVO_H
#define ACERVO_H

#include "bancodedados.h"
#include <string>

// criar os codigos especificos de cada genero em um arquivo separado

enum CODIGOS_GENEROS_ACERVO
{
    MATEMATICA,
    FISICA,
    ARTE,
    PROGRAMACAO,
    CULINARIA,
    HISTORIA
};

// ACERVO NAO É virtual (pura), da pra criar um acervo sem ter nenhum exemplar (meio estranho mas ta certo)
class Acervo
{
private:
    std::string _autor;
    int _ano_publicacao;
    std::string _titulo;
    CODIGOS_GENEROS_ACERVO _genero;
    int _codigo;

public:
    // Construtor
    Acervo(std::string autor, int ano_publicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero, int codigo);
    ~Acervo();

    // getters
    std::string get_autor() const;
    int get_ano_publicacao() const;
    std::string get_titulo() const;
    CODIGOS_GENEROS_ACERVO get_genero() const;
    int get_codigo() const;

    protected:
    const char* file = "biblioteca.db";
    BD bibdados;
};

#endif // ACERVO_H
