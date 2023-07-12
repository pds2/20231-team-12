#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <string>
#include <vector>

#include "exemplar.h"
#include "acervo.h"
#include "perfil_usuario.hpp"
//dedados.h"

class aluno_com_multa_e
{
};
class ja_possui_mutos_livros_e
{
};
class nao_possui_esse_livro_e
{
};
class ja_possui_esse_livro_e
{
};

class Aluno : public Perfil_usuario
{
private:
    std::vector<Exemplar *> livros_com_aluno;
    const char* file = "biblioteca.db";
public:
    /*
     * @brief Constrói um aluno.
     * @param email Email do aluno.
     * @param senha Senha do aluno.
     */
    Aluno(std::string email, int senha);


    virtual ~Aluno();



    /*
     * @brief Pega todos os livros emprestados ao aluno.
     */
    std::vector<Exemplar *> get_livros_com_aluno();
    /*
     * @brief Pega o número de livros emprestados ao aluno.
     */
    int get_n_exemplares();
    /*
     * @brief Empresa um livro ao aluno.
     * @param livro Endereço do livro a ser emprestado.
     */
    void emprestar_livro(Exemplar *livro);

    /*
     * @brief Devolve um livro do aluno.
     * @param codigo Código do livro a ser emprestado.
     */
    void devolver_livro(int codigo);
    /*
     * @brief Consulta a existência de um acervo na biblioteca.
     * @param titulo Titulo do acervo a ser buscado.
     */
    void consultar_acervo(std::string titulo) override;

    /*
     * @brief Consulta a multa de todos os livros emprestados.
     */
    void consultar_multa_total();
    /*
     * @brief Salva o aluno no arquivo.
     */
    int salvar_aluno_no_arquivo();

    /// @brief Persistence: metodo criado para auxiliar no acesso aos exemplares.
    void BDauxiliar(std::string codigosecreto);

protected:
    //Persistence
    static void executar_sql(const char* f, string comandosql, string avisoerro);
    void bd_inserir_tabela_usuarios(const char* f, Perfil_usuario* user);
    void bd_inserir_aluno(const char* f, Aluno* aluno);
    void bd_inserir_alunoexemplar(const char* f, Aluno* aluno, Exemplar* item);
    void bd_acessar_tabela_exemplaresaluno(const char* f, Aluno* aluno);
    void bd_acessar_acervoportitulo(const char* f, std::string titulo);
    void bd_remover_exemplaraluno(const char *f, int exemplarid);
    bool checkUsuarioid(const char* f, Perfil_usuario* user);
    bool checkUsuarioemail(const char* f, Perfil_usuario* user);
    bool checkTabelaExiste(const char*f, string nome_tabela);
    void updateExemplarEmprestado(const char* f, Exemplar* item, int umouzero);
    void UpdateMultaExemplarAluno(const char* f, Exemplar* item);
    void bd_remover_usuario(const char* f, Perfil_usuario* user, string codigosecreto);

};

#endif