#ifndef CADASTROCOLABORADORES_H
#define CADASTROCOLABORADORES_H

#include <QDialog>
#include <QtSql>

#include "pessoa.h"

namespace Ui {
class cadastroColaboradores;
}

class cadastroColaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroColaboradores(QWidget *parent = nullptr);
    ~cadastroColaboradores();

private slots:
    void on_btnCadastrarCol_clicked();

    void on_btnCancelarCol_clicked();

private:
    Ui::cadastroColaboradores *ui;

signals:
    // Sinal emitido quando um colaborador é cadastrado
    void colaboradorCadastrado(int id);
};

#endif // CADASTROCOLABORADORES_H
