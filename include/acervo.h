#ifndef ACERVO_H
#define ACERVO_H

#include <string>
#include "bancodedados.h"

// ACERVO NAO É virtual (pura), da pra criar um acervo sem ter nenhum exemplar (meio estranho mas ta certo)
class Acervo 
{
private:
    std::string _autor;
    int _ano_publicacao;
    std::string _titulo;
    std::string _genero;
    int _codigo;

protected:
    const char* file = "biblioteca.db";

public:
    // Construtor
    Acervo(std::string autor, int ano_publicacao, std::string titulo, std::string genero, int codigo);
    ~Acervo();

    // getters
    std::string get_autor() const;
    int get_ano_publicacao() const;
    std::string get_titulo() const;
    std::string get_genero() const;
    int get_codigo() const;

};

#endif // ACERVO_H
