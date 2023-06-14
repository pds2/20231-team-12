#ifndef ACERVO_H
#define ACERVO_H

#include <string>

using namespace std;
class Acervo {
public:
    //Construtor
    Acervo(string autor, int anoPublicacao, string titulo, string genero, int codigo);
    virtual ~Acervo();

    //getters
    string getAutor() const;
    int getAnoPublicacao() const;
    string getTitulo() const;
    string getGenero() const;
    int getCodigo() const;

    //setters
    /*string setAutor() const;
    int setAnoPublicacao() const;
    string setTitulo() const;
    string setGenero() const;
    int setCodigo() const;*/


private:
    string autor;
    int anoPublicacao;
    string titulo;
    string genero;
    int codigo;
};

#endif  // ACERVO_H
