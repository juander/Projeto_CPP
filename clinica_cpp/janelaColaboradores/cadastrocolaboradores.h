#ifndef CADASTROCOLABORADORES_H
#define CADASTROCOLABORADORES_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

#include "../classPessoa/pessoa.h"

namespace Ui {
class cadastroColaboradores;
}

class cadastroColaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroColaboradores(QWidget *parent = nullptr, const QString &modo = "Cadastrar", int id_colaborador = -1);
    ~cadastroColaboradores();

    void setIdColaborador(int id);
    int getIdColaborador();
    void setModo(const QString &modo, int id_colaborador);

private slots:
    void on_btnCadastrarCol_clicked();
    void on_btnCancelarCol_clicked();

signals:
    // Sinal emitido quando um colaborador é cadastrado
    void colaboradorCadastrado(int id);

private:
    Ui::cadastroColaboradores *ui;
    int idColaborador;
    QString tipoUso;
};

#endif // CADASTROCOLABORADORES_H
