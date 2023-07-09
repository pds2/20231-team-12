#include "../include/bibliotecario.hpp"
#include "../include/bancodedados.h"

Papel_do_usuario Bibliotecario::set_papel_usuario()
{
    return BIBLIOTECARIO;
}

BD bibdados;

void Bibliotecario::adicionar_acervo(Acervo acervo_novo)
{
    bibdados.bd_inserir_tabela_acervos(file, &acervo_novo);
}

void Bibliotecario::adicionar_exemplar(Exemplar exemplar_novo)
{
    bibdados.bd_inserir_tabela_exemplares(file, &exemplar_novo);
}

void Bibliotecario::remover_acervo(Acervo acervo_deletado)
{
    bibdados.bd_remover_acervo(file, &acervo_deletado);
}

void Bibliotecario::remover_exemplar(Exemplar exemplar_deletado)
{
    bibdados.bd_remover_exemplarespecifico(file, &exemplar_deletado);
}

void Bibliotecario::emprestimo_de_exemplar(Exemplar exemplar_emprestado)
{
    bibdados.updateExemplarEmprestado(file, &exemplar_emprestado, 1);
}

void Bibliotecario::devolucao_de_exemplar(Exemplar exemplar_devolvido)
{
    bibdados.updateExemplarEmprestado(file, &exemplar_devolvido, 0);
}

void Bibliotecario::consulta_geral_acervos(Exemplar especifico){

    bibdados.bd_acessar_tebela_acervos(file);
    bibdados.checkNumExemplares(file, &especifico);

}