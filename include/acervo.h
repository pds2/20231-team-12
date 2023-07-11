#ifndef ACERVO_H
#define ACERVO_H

// #include "bancodedados.h"
#include <fstream>
#include <string>
#include <iostream>

// criar os codigos especificos de cada genero em um arquivo separado

// ACERVO NAO É virtual (pura), da pra criar um acervo sem ter nenhum exemplar (meio estranho mas ta certo)
class Acervo
{
private:
    int _codigo;
    std::string _autor;
    std::string _titulo;
    int _ano_publicacao;
    int _genero;

public:
    /*
     * @brief Constroi um acervo.
     * @param codigo Código do acervo.
     * @param autor Autor do acervo.
     * @param titulo Título do acervo.
     * @param ano_publicacao Ano de publicação do acervo.
     * @param genero Gênero do acervo.
     */
    Acervo(int codigo, std::string autor, std::string titulo, int ano_publicacao, int genero);
    /*
     * @brief Destrói o acervo.
     */
    ~Acervo();
    bool operator<(const Acervo &acervo_custom) const;

    /*
     * @brief Compara dois acervos com o operador <.
     */
    bool operator<(const Acervo &acervo_custom) const;
    /*
     * @brief Pega o autor do acervo.
     */
    std::string get_autor() const;
    /*
     * @brief Pega o ano de publicação do acervo.
     */
    int get_ano_publicacao() const;
    /*
     * @brief Pega o título do acervo.
     */
    std::string get_titulo() const;
    /*
     * @brief Pega o gênero do acervo.
     */
    int get_genero() const;
    /*
     * @brief Pega o código do acervo.
     */
    int get_codigo() const;
    /*
     * @brief Salva o acervo no arquivo.
     */
    int salvar_acervo_no_arquivo();
};

#endif // ACERVO_H
