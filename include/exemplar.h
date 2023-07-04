#ifndef EXEMPLAR_H
#define EXEMPLAR_H

<<<<<<< HEAD
#include "acervo.h"


class Exemplar : public Acervo {
public:
    Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
             bool emprestado, int dataAquisicao, int codigoEspecifico, int dataDevolucao);

    // Métodos getters
    bool isEmprestado() const;
    int getDataAquisicao() const;
    int getCodigoEspecifico() const;
    int getDataDevolucao() const;

    //métodos
    //void mostraMulta(int dataAtual) const;
    int calculaMulta() const;


private:

    bool emprestado;
    int dataAquisicao;
    int codigoEspecifico;
    int dataDevolucao;
};

#endif  // EXEMPLAR_H
=======
#include <ctime>

#include "acervo.h"

// criar os tipos de codigo
enum CODIGOS_SUBGENEROS_EXEMPLARES
{
    MATEMATICA_BASICA,
    CALCULO_1,
    CALCULO_2
};

class Exemplar : public Acervo
{
private:
    bool _emprestado;
    float _multa;
    struct tm _dia_emprestado;
    CODIGOS_SUBGENEROS_EXEMPLARES _codigo_exemplar;

public:
    Exemplar(std::string autor, int ano_publicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero, int codigo, CODIGOS_SUBGENEROS_EXEMPLARES _codigo_exemplar);
    bool get_emprestado();
    tm get_dia_emprestado();
    CODIGOS_SUBGENEROS_EXEMPLARES get_codigo_exemplar();

    void emprestar_exemplar();
    void incrementar_multa();
};

#endif
>>>>>>> c08a5ddf6fdc1e401968fd7bbcf64b6c10236287
