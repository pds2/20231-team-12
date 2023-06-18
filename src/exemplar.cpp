#include "exemplar.h"
#include <iostream>
#include <ctime>

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

void Exemplar::calculaMulta() const {

    //pega a data de devolucao que devera estar em formato 18/06/2023 -> 18062023
    int dataDevolucao = getDataDevolucao();

    int diaDevolucao, mesDevolucao, anoDevolucao;
    int diasAtraso = 0; 


//utilizando biblioteca "ctime"
    std::time_t now = std::time(nullptr);//obter a data e hora atuais
    std::tm* current_time = std::localtime(&now); //converter o valor de tempo em uma estrutura std::tm contendo informações sobre o ano, mês, dia.
    
    //extraindo os valores de dia atual, mes atual e ano atual da estrutura std::tm
    int diaAtual = current_time->tm_mday;
    int mesAtual = current_time->tm_mon + 1; //retorna o mês atual, onde janeiro é representado por 0 e dezembro por 11, convertendo para 1 a 12(soma-se+1)
    int anoAtual = current_time->tm_year + 1900; //1900 - convenção C Library

    int dataAtual = diaAtual + mesAtual * 100 + anoAtual* 10000; //operação q combina o ano, mês e dia em formato de data numérica 17/06/23 -> 20230617

    diaDevolucao = dataDevolucao % 100;
    mesDevolucao = (dataDevolucao / 100) % 100;
    anoDevolucao = dataDevolucao / 10000;

if (anoAtual > anoDevolucao || (anoAtual == anoDevolucao && mesAtual > mesDevolucao) || (anoAtual == anoDevolucao && mesAtual == mesDevolucao && diaAtual > diaDevolucao)) {
        // Calcula a diferença em dias apenas se a data atual for posterior à data de devolução
        std::tm devolucao_time = { 0 };
        devolucao_time.tm_mday = diaDevolucao;
        devolucao_time.tm_mon = mesDevolucao - 1;
        devolucao_time.tm_year = anoDevolucao - 1900;

        std::time_t devolucao_timestamp = std::mktime(&devolucao_time);

        std::tm atual_time = { 0 };
        atual_time.tm_mday = diaAtual;
        atual_time.tm_mon = mesAtual - 1;
        atual_time.tm_year = anoAtual - 1900;

        std::time_t atual_timestamp = std::mktime(&atual_time);

        // Calcula a diferença em segundos entre as datas
        std::time_t diff_seconds = std::difftime(atual_timestamp, devolucao_timestamp);

        // Converte a diferença em segundos para dias
        diasAtraso = static_cast<int>(diff_seconds) / (60 * 60 * 24);
    }
   
    if (diasAtraso > 0) {
        float multa = diasAtraso;
         std::cout << "Multa de: R$ " << multa << std::endl;
    } else {
         std::cout << "Nenhuma multa!" << std::endl;;
    }
}