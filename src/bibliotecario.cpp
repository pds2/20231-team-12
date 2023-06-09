#include "../include/bibliotecario.hpp"

Papel_do_usuario Bibliotecario::set_papel_usuario()
{
    return BIBLIOTECARIO;
}

Papel_do_usuario Bibliotecario::get_papel_usuario()
{
    return papel;
}

void Bibliotecario::adicionar_acervo(Acervo acervo_novo)
{
}

void Bibliotecario::remover_acervo(Acervo acervo_deletado)
{
}

void Bibliotecario::emprestimo_de_exemplar(Exemplar exemplar_emprestado)
{
}

void Bibliotecario::devolucao_de_exemplar(Exemplar exemplar_devolvido)
{
}