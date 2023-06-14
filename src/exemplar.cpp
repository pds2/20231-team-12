#include "exemplar.h"
#include <iostream>

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

void Exemplar::mostraMulta(int dataAtual) const {
    int multa = calculaMulta(dataAtual);
    if (multa > 0) {
        std::cout << "Multa de: R$ " << multa << std::endl;
    } else {
        std::cout << "Nenhuma multa!" << std::endl;
    }
}

int Exemplar::calculaMulta(int dataAtual) const {
    int diasAtraso = dataAtual - dataDevolucao;
    if (diasAtraso > 0) {
        float multa = diasAtraso;
        return multa;
    } else {
        return 0;
    }
}