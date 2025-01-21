#ifndef CADASTROPACIENTES_H
#define CADASTROPACIENTES_H

#include <QDialog>
#include <QtSql>

#include "pessoa.h"

namespace Ui {
class cadastroPacientes;
}

class cadastroPacientes : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroPacientes(QWidget *parent = nullptr);
    ~cadastroPacientes();

private slots:

    // Método para cadastrar um novo paciente
    void on_btnCadastrarPac_clicked();

    // Método para cancelar o cadastro    
    void on_btnCancelarPac_clicked();

private:
    Ui::cadastroPacientes *ui;

signals:
    // Sinal emitido quando um paciente é cadastrado
    void pacienteCadastrado(int id);
};

#endif // CADASTROPACIENTES_H
