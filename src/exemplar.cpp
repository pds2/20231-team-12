#include "../include/exemplar.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>

#include <iomanip>

Exemplar::Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
                   bool emprestado, int dataAquisicao, int codigoEspecifico)
    : Acervo(autor, anoPublicacao, titulo, genero, codigo), emprestado(emprestado), dataAquisicao(dataAquisicao),
      codigoEspecifico(codigoEspecifico)  {
        
}


int Exemplar::getDataAquisicao() const {
    return dataAquisicao;
}

int Exemplar::getCodigoEspecifico() const {
    return codigoEspecifico;
}
int Exemplar::calculaDataDevolucaoSistema() {
    std::tm aquisicao_time = { 0 };
    aquisicao_time.tm_mday = dataAquisicao % 100;
    aquisicao_time.tm_mon = (dataAquisicao / 100) % 100 - 1;
    aquisicao_time.tm_year = dataAquisicao / 10000 - 1900;

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

   // cout<< " 1 data de devolucao do sistema: "<< dataDevolucaoCorreto << endl;

    return dataDevolucaoCorreto;
}


int Exemplar::calculaMulta() {
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


    //printando

// Converter dataDevolucaoPonto para std::tm
std::time_t dataDevolucaoPontoTimeT = std::chrono::system_clock::to_time_t(dataDevolucaoPonto);
std::tm* dataDevolucaoPontoTM = std::localtime(&dataDevolucaoPontoTimeT);


// Imprimir a dataDevolucaoPonto
std::cout << "\nData de devolucao: "
          << std::put_time(dataDevolucaoPontoTM, "%Y-%m-%d %H:%M:%S")
          << std::endl;

// Converter dataAtualPonto para std::tm
std::time_t dataAtualPontoTimeT = std::chrono::system_clock::to_time_t(dataAtualPonto);
std::tm* dataAtualPontoTM = std::localtime(&dataAtualPontoTimeT);

// Imprimir a dataAtual
std::cout << "Data atual: "
          << std::put_time(dataAtualPontoTM, "%Y-%m-%d %H:%M:%S")
          << std::endl;

//fim printando

    // Calcula a diferença entre a data atual e a data de devolução em dias
    std::chrono::duration<int, std::ratio<86400>> duracao = std::chrono::duration_cast<std::chrono::duration<int, std::ratio<86400>>>(dataAtualPonto - dataDevolucaoPonto);
    int diasAtraso = duracao.count();

    cout<< "Dias de atraso: "<< diasAtraso << endl;

    // Se não houver atraso, a multa é zero
    if (diasAtraso <= 0) {
            std::cout << "Nenhuma multa!" << std::endl;
        return 0;
    }
  else{
    // Calcula o valor da multa (assumindo uma taxa fixa por dia)
    int taxaMultaPorDia = 1;  // Ajuste esse valor conforme necessário
    int multa = taxaMultaPorDia * diasAtraso;

    std::cout << "Multa de: R$ " << multa << std::endl;
    return multa;
 }
}



/