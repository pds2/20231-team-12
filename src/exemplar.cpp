#include "../include/exemplar.h"

Exemplar::Exemplar(std::string autor, int ano_publicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero,
                   int codigo, CODIGOS_SUBGENEROS_EXEMPLARES _codigo_exemplar)
    : Acervo(autor, ano_publicacao, titulo, genero, codigo)
{

    _emprestado = 0;
    dia_emprestado = 0;
    _multa = 0;
};

bool get_emprestado();
time_t get_dia_emprestado();
int get_codigo_exemplar();

void incrementar_multa();
}
;