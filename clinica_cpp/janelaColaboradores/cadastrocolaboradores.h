#ifndef CADASTROCOLABORADORES_H
#define CADASTROCOLABORADORES_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

#include "../classPessoa/pessoa.h"                                                                                        // Inclui o cabeçalho da classe Pessoa

namespace Ui {
class cadastroColaboradores;                                                                                              // Declaração da classe cadastroColaboradores
}

class cadastroColaboradores : public QDialog                                                                              // Declaração da classe cadastroColaboradores que herda de QDialog
{
    Q_OBJECT                                                                                                              // Macro Q_OBJECT necessária para todas as classes que definem sinais e slots

public:
    explicit cadastroColaboradores(QWidget *parent = nullptr, const QString &modo = "Cadastrar", int id_colaborador = -1); // Construtor
    ~cadastroColaboradores();                                                                                             // Destrutor

    void setIdColaborador(int id);                                                                                        // Define o ID do colaborador
    int getIdColaborador();                                                                                               // Retorna o ID do colaborador
    void setModo(const QString &modo, int id_colaborador);                                                                // Define o modo (Cadastrar ou Editar)

private slots:
    void on_btnCadastrarCol_clicked();                                                                                    // Método para cadastrar um novo colaborador
    void on_btnCancelarCol_clicked();                                                                                     // Método para cancelar o cadastro

signals:
    void colaboradorCadastrado(int id);                                                                                   // Sinal emitido quando um colaborador é cadastrado

private:
    Ui::cadastroColaboradores *ui;                                                                                        // Ponteiro para a interface do usuário
    int idColaborador;                                                                                                    // ID do colaborador
    QString tipoUso;                                                                                                      // Tipo de uso (Cadastrar ou Editar)
};

#endif // CADASTROCOLABORADORES_H
