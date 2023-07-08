#include "../include/exemplar.h"
<<<<<<< HEAD

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
=======
#include <iostream>
#include <ctime>

Exemplar::Exemplar(std::string autor, int anoPublicacao, std::string titulo, std::string genero, float codigo,
                   bool emprestado, int dataAquisicao, int codigoEspecifico, int dataDevolucao)
    : Acervo(autor, anoPublicacao, titulo, genero, codigo), emprestado(emprestado), dataAquisicao(dataAquisicao),
      codigoEspecifico(codigoEspecifico), dataDevolucao(dataDevolucao) {
        
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
int Exemplar::calculaDataDevolucao() {
    std::tm aquisicao_time = { 0 };
    aquisicao_time.tm_mday = dataAquisicao % 100;
    aquisicao_time.tm_mon = (dataAquisicao / 100) % 100 - 1;
    aquisicao_time.tm_year = dataAquisicao / 10000 - 1900;

    std::time_t aquisicao_timestamp = std::mktime(&aquisicao_time);

    // Adiciona um mês à data de aquisição
    std::tm devolucao_time = *std::localtime(&aquisicao_timestamp);
    devolucao_time.tm_mon += 1;

    std::time_t devolucao_timestamp = std::mktime(&devolucao_time);

    std::tm* devolucao_date = std::localtime(&devolucao_timestamp);

    dataDevolucao = (devolucao_date->tm_year + 1900) * 10000 + (devolucao_date->tm_mon + 1) * 100 + devolucao_date->tm_mday;

    return dataDevolucao;
}
int Exemplar::calculaMulta() {

    //pega a data de devolucao que devera estar em formato 18/06/2023 -> 18062023
    dataDevolucao = calculaDataDevolucao();

    int diaDevolucao, mesDevolucao, anoDevolucao;
    int diasAtraso = 0; 
    int multa = 0;


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

        /*std::mktime() é uma função da biblioteca <ctime> que converte uma estrutura std::tm em um valor de 
        tempo (std::time_t). Nesse caso, estamos convertendo a estrutura devolucao_time que contém a data de 
        devolução para um valor de tempo.*/
        std::time_t devolucao_timestamp = std::mktime(&devolucao_time);

        /*Aqui, estamos criando uma estrutura std::tm chamada atual_time e inicializando todos os seus campos como zero.*/
        std::tm atual_time = { 0 };
        atual_time.tm_mday = diaAtual;
        atual_time.tm_mon = mesAtual - 1;
        atual_time.tm_year = anoAtual - 1900;


        /*Da mesma forma que fizemos para a data de devolução, estamos convertendo a estrutura atual_time, que 
        contém a data atual, em um valor de tempo std::time_t.*/
        std::time_t atual_timestamp = std::mktime(&atual_time);

        // Calcula a diferença em segundos entre as datas
        std::time_t diff_seconds = std::difftime(atual_timestamp, devolucao_timestamp);
        /*std::difftime() é uma função da biblioteca <ctime> que calcula a diferença de tempo entre dois valores de tempo (std::time_t) em segundos.*/


        // Converte a diferença em segundos para dias
        diasAtraso = static_cast<int>(diff_seconds) / (60 * 60 * 24);
        /*Estamos convertendo a diferença de tempo em segundos (diff_seconds) para dias, dividindo-a por 60 segundos
         (para obter minutos), depois por 60 minutos (para obter horas) e finalmente por 24 horas (para obter dias).
         O static_cast<int> é usado para converter o valor resultante em um número inteiro, pois estamos interessados
         apenas nos dias inteiros de atraso.*/
    }
   
    if (diasAtraso > 0) {
        multa = diasAtraso * 1;
        std::cout << "Multa de: R$ " << multa << std::endl;
    } else {
         std::cout << "Nenhuma multa!" << std::endl;;
    }
    
    return multa;
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
}