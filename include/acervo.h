#ifndef ACERVO_H
#define ACERVO_H

#include <string>

<<<<<<< HEAD
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
=======
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
    std::string get_autor();
    int get_ano_publicacao();
    std::string get_titulo();
    CODIGOS_GENEROS_ACERVO get_genero();
    int get_codigo();
};

#endif // ACERVO_H
>>>>>>> c08a5ddf6fdc1e401968fd7bbcf64b6c10236287
