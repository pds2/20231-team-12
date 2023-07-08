#include "../include/bibliotecario.hpp"
<<<<<<< HEAD
#include "../include/bancodedados.h"
=======
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286

Papel_do_usuario Bibliotecario::set_papel_usuario()
{
    return BIBLIOTECARIO;
}

void Bibliotecario::adicionar_acervo(Acervo acervo_novo)
{
<<<<<<< HEAD
    bibdados.bd_inserir_tabela_acervos(file, &acervo_novo);
}

void Bibliotecario::adicionar_exemplar(Exemplar exemplar_novo)
{
    bibdados.bd_inserir_tabela_exemplares(file, &exemplar_novo);
=======
}

void Bibliotecario::adicionar_exemplar(Exemplar exemplar_novo){

>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
}

void Bibliotecario::remover_acervo(Acervo acervo_deletado)
{
<<<<<<< HEAD
    bibdados.bd_remover_acervo(file, &acervo_deletado);
}

void Bibliotecario::remover_exemplar(Exemplar exemplar_deletado)
{
    bibdados.bd_remover_exemplarespecifico(file, &exemplar_deletado);
=======
}

void Bibliotecario::remover_exemplar(Exemplar exemplar_deletado){
    
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
}

void Bibliotecario::emprestimo_de_exemplar(Exemplar exemplar_emprestado)
{
<<<<<<< HEAD
    bibdados.updateExemplarEmprestado(file, &exemplar_emprestado, 1);
=======
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
}

void Bibliotecario::devolucao_de_exemplar(Exemplar exemplar_devolvido)
{
<<<<<<< HEAD
    bibdados.updateExemplarEmprestado(file, &exemplar_devolvido, 0);
}

void Bibliotecario::consulta_geral_acervos(Exemplar especifico){

    bibdados.bd_acessar_tebela_acervos(file);
    bibdados.checkNumExemplares(file, &especifico);

=======
>>>>>>> e72aed66b4c53ba20f50d0834f4e0b2ac7a28286
}