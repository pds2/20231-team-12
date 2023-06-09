#include "exemplar.h"

Exemplar::Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
                   bool emprestado, int dataAquisicao, int codigoEspecifico, int dataDevolucao)
    : Acervo(autor, anoPublicacao, titulo, genero, codigo), emprestado(emprestado), dataAquisicao(dataAquisicao),
      codigoEspecifico(codigoEspecifico), dataDevolucao(dataDevolucao) {
}

bool Exemplar::isEmprestado() const {
    return emprestado;
    if (emprestado == true){
        getDataDevolucao();
    }
}

int Exemplar::getDataAquisicao() const {
    return dataAquisicao;
}

int Exemplar::getCodigoEspecifico() const {
    return codigoEspecifico;
}

int Exemplar::getDataDevolucao() const{
    return dataDevolucao;
}
