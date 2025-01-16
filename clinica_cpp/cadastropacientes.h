#ifndef CADASTROPACIENTES_H
#define CADASTROPACIENTES_H

#include <QDialog>
#include <QtSql>

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
    void on_btnCadastrar_clicked();

    void on_btnCancelar_clicked();

private:
    Ui::cadastroPacientes *ui;

signals:
    void pacienteCadastrado(int id);
};

#endif // CADASTROPACIENTES_H
