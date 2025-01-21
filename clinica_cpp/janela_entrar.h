#ifndef JANELA_ENTRAR_H
#define JANELA_ENTRAR_H

#include "Conexao.h"
#include <QDialog>

namespace Ui {
class janela_entrar;
}

class MainWindow;

class janela_entrar : public QDialog
{
    Q_OBJECT

public:
    explicit janela_entrar(QWidget *parent = nullptr, Conexao *conexao = nullptr);
    ~janela_entrar();

    bool logado;

    QString nome, cargo;

private slots:
    void on_btnEnt_clicked();
    void on_btnMostrar_clicked();
    void on_btnCancelar_clicked();

private:
    Ui::janela_entrar *ui;
    Conexao *conexao;
};

#endif // JANELA_ENTRAR_H
