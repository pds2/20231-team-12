#include "../include/exemplar.h"

Exemplar::Exemplar(std::string autor, int ano_publicacao, std::string titulo, CODIGOS_GENEROS_ACERVO genero,
                   int codigo, CODIGOS_SUBGENEROS_EXEMPLARES _codigo_exemplar)
    : Acervo(autor, ano_publicacao, titulo, genero, codigo)
{

    _emprestado = 0;
    _multa = 0;
};

bool Exemplar::get_emprestado()
{
    return _emprestado;
}

tm Exemplar::get_dia_emprestado()
{
    return _dia_emprestado;
}

CODIGOS_SUBGENEROS_EXEMPLARES Exemplar::get_codigo_exemplar()
{
    return _codigo_exemplar;
}

void Exemplar::emprestar_exemplar()
{
    time_t dia_hoje = time(NULL);
    _dia_emprestado = *localtime(&dia_hoje);

    _emprestado = 1;
    bibdados.updateExemplarEmprestado(file, &(*this), 1);
}
void Exemplar::incrementar_multa()
{
    time_t dia_atual = time(NULL);
    struct tm dia_atual_comparacao = *localtime(&dia_atual);

    if (dia_atual_comparacao.tm_mday - _dia_emprestado.tm_mday >= 5)
    { // COMPARAR O MES TAMBEM
        _multa += 2;
        bibdados.UpdateMultaExemplarAluno(file, &(*this));
    }
}

//Persistence:
float Exemplar::get_multa(){
    return _multa;
}