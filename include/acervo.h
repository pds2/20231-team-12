#ifndef ACERVO_H
#define ACERVO_H

#include <string>

using namespace std;

/**
 * @brief Classe Acervo, base
 */
class Acervo {
public:
    /**
     * @brief Construtor da classe
     */
    Acervo(string autor, int anoPublicacao, string titulo, string genero, int codigo);

    virtual ~Acervo();

    //getters
     /**
     * @brief Pega o autor
     */
    string getAutor() const;

    /**
     * @brief Pega o ano de publicação
     */
    int getAnoPublicacao() const;

    /**
     * @brief Pega o Título
     */
    string getTitulo() const;

    /**
     * @brief Pega o Gênero
     */
    string getGenero() const;

    /**
     * @brief Pega o código
     */
    int getCodigo() const;



private:
    string autor;
    int anoPublicacao;
    string titulo;
    string genero;
    int codigo;
};

#endif  // ACERVO_H
