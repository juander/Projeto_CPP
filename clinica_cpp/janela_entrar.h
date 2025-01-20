#ifndef JANELA_ENTRAR_H
#define JANELA_ENTRAR_H

#include "Conexao.h"
#include <QDialog>

namespace Ui {
class janela_entrar;
}

class janela_entrar : public QDialog
{
    Q_OBJECT

public:
    explicit janela_entrar(QWidget *parent = nullptr);
    ~janela_entrar();
    bool logado;
    Conexao conex;
    QString nome, cargo;
    QString getNome();
    QString getCargo();

private slots:
    void on_btnEntrar_clicked();

private:
    Ui::janela_entrar *ui;
};

#endif // JANELA_ENTRAR_H
