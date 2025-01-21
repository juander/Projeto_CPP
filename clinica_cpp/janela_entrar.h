#ifndef JANELA_ENTRAR_H
#define JANELA_ENTRAR_H

#include "Conexao.h"
#include <QDialog>

namespace Ui {
class janela_entrar;
}

class janela_entrar : public QDialog {
    Q_OBJECT

public:
    explicit janela_entrar(QWidget *parent = nullptr, Conexao *conexao = nullptr);
    ~janela_entrar();

    bool logadoJanela;
    QString nome, clinica, cargo;
    int id;

signals:
    void loginRealizado(const int &id, const QString &nome, const QString &clinica, const QString &cargo);

private slots:
    void on_btnEnt_clicked();
    void on_btnMostrar_clicked();
    void on_btnCancelar_clicked();

private:
    Ui::janela_entrar *ui;
    Conexao *conexao;
};

#endif // JANELA_ENTRAR_H
