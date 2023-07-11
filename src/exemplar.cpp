#include "../include/exemplar.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>

#include <iomanip>

Exemplar::Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
                   bool emprestado,  int codigoEspecifico)
    : Acervo(autor, anoPublicacao, titulo, genero, codigo), emprestado(emprestado),
      codigoEspecifico(codigoEspecifico)  {
        
}

int Exemplar::getdataEmprestimo() const {
    return dataEmprestimo;
}

 //set -> Necessário para realizar os test cases
void Exemplar::setDataEmprestimo(int dataEmprestimo) {
    this->dataEmprestimo = dataEmprestimo;
}

int Exemplar::getCodigoEspecifico() const {
    return codigoEspecifico;
}
int Exemplar::calculaDataDevolucaoSistema() {
    std::tm aquisicao_time = { 0 };
    aquisicao_time.tm_mday = getdataEmprestimo() % 100;
    aquisicao_time.tm_mon = (getdataEmprestimo() / 100) % 100 - 1;
    aquisicao_time.tm_year = getdataEmprestimo() / 10000 - 1900;

    std::time_t aquisicao_timestamp = std::mktime(&aquisicao_time);

    // Adiciona um mês à data de aquisição
    std::tm devolucao_time = *std::localtime(&aquisicao_timestamp);
    devolucao_time.tm_mon += 1;

    // Ajusta o ano e o mês caso o valor exceda os limites
    if (devolucao_time.tm_mon > 11) {
        devolucao_time.tm_mon = 0;
        devolucao_time.tm_year += 1;
    }

    std::time_t devolucao_timestamp = std::mktime(&devolucao_time);

    std::tm* devolucao_date = std::localtime(&devolucao_timestamp);

    int dataDevolucaoCorreto = (devolucao_date->tm_year + 1900) * 10000 + (devolucao_date->tm_mon + 1) * 100 + devolucao_date->tm_mday;

    return dataDevolucaoCorreto;
}


void Exemplar::calculaMulta() {
    int dataDevolucaoSistema = this->calculaDataDevolucaoSistema();  // Obtém a data de devolução calculada pelo sistema


    std::time_t horaAtual = std::time(nullptr);  // Obtém a hora atual
    std::tm* dataAtual = std::localtime(&horaAtual);  // Converte a hora atual para uma estrutura tm
    
    // Cria a data atual usando a biblioteca chrono
    std::chrono::system_clock::time_point dataAtualPonto = std::chrono::system_clock::from_time_t(horaAtual);

    // Obtém a data de devolução usando a biblioteca chrono
    std::tm dataDevolucao = { 0 };
    dataDevolucao.tm_mday = dataDevolucaoSistema % 100;
    dataDevolucao.tm_mon = (dataDevolucaoSistema / 100) % 100 - 1;
    dataDevolucao.tm_year = dataDevolucaoSistema / 10000 - 1900;
    std::time_t dataDevolucaoTimestamp = std::mktime(&dataDevolucao);
    std::chrono::system_clock::time_point dataDevolucaoPonto = std::chrono::system_clock::from_time_t(dataDevolucaoTimestamp);

    // Calcula a diferença entre a data atual e a data de devolução em dias
    std::chrono::duration<int, std::ratio<86400>> duracao = std::chrono::duration_cast<std::chrono::duration<int, std::ratio<86400>>>(dataAtualPonto - dataDevolucaoPonto);
    int diasAtraso = duracao.count();

    cout<< "Dias de atraso: "<< diasAtraso << endl;

    // Se não houver atraso, a multa é zero
    if (diasAtraso <= 0) {
            multa = 0;
    }
  else{
    // Calcula o valor da multa (assumindo uma taxa fixa por dia de 1 real)
    int taxaMultaPorDia = 1;  // multa de 1 real por dia
    multa = taxaMultaPorDia * diasAtraso;
 }
}

int Exemplar::getMulta() {
    return multa; //pega o valor da multa que foi colculado no método calculaMulta
}


