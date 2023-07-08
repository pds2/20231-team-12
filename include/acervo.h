#ifndef ACERVO_H
#define ACERVO_H

#include "bancodedados.h"
#include <string>

<<<<<<< HEAD
// criar os codigos especificos de cada genero em um arquivo separado

=======
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
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
<<<<<<< HEAD
    std::string get_autor();
    int get_ano_publicacao();
    std::string get_titulo();
    CODIGOS_GENEROS_ACERVO get_genero();
    int get_codigo();

protected:
    const char* file = "biblioteca.db";
    BD bibdados;
=======
    std::string get_autor() const;
    int get_ano_publicacao() const;
    std::string get_titulo() const;
    CODIGOS_GENEROS_ACERVO get_genero() const;
    int get_codigo() const;
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
};

#endif // ACERVO_H
