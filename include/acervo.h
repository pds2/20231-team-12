#ifndef ACERVO_H
#define ACERVO_H

#include <string>

// criar os codigos especificos de cada genero em um arquivo separado

using namespace std;
class Acervo
{
public:
    // Construtor
    Acervo(string autor, int anoPublicacao, string titulo, int genero, int codigo);

    // getters
    string getAutor() const;
    int getAnoPublicacao() const;
    string getTitulo() const;
    int getGenero() const;
    int getCodigo() const;

    // setters - nao precisa !!
    /*
    string setAutor() const;
    int setAnoPublicacao() const;
    string setTitulo() const;
    string setGenero() const;
    string setCodigo() const;
    */

private:
    string autor;
    int anoPublicacao;
    string titulo;
    int genero;
    int codigo;
};

#endif // ACERVO_H
