#ifndef CADASTROSESSAO_H
#define CADASTROSESSAO_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class cadastroSessao;
}

class cadastroSessao : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroSessao(QWidget *parent = nullptr);
    ~cadastroSessao();

private slots:

    // Método para cadastrar um novo paciente
    void on_btnCadastrarSes_clicked();

    // Método para cancelar o cadastro
    void on_btnCancelarSes_clicked();

private:
    Ui::cadastroSessao *ui;

signals:
    // Sinal emitido quando um paciente é cadastrado
    void sessaoCadastrada(int id);
};

#endif // CADASTROSESSAO_H
