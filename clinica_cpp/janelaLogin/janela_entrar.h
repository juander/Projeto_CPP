#ifndef JANELA_ENTRAR_H
#define JANELA_ENTRAR_H

#include <QDialog>

#include "../classConexaoBanco/Conexao.h"

namespace Ui {
class janela_entrar;
}

class janela_entrar : public QDialog {
    Q_OBJECT

public:
    explicit janela_entrar(QWidget *parent = nullptr, Conexao *conexao = nullptr);
    ~janela_entrar();

    bool getLogadoJanela();
    QString getNome();
    QString getClinica();
    QString getCargo();
    int getId();

    void setLogadoJanela(bool login = false);
    void setNome(QString nom = nullptr);
    void setClinica(QString clin = nullptr);
    void setCargo(QString carg = nullptr);
    void setId(int codigo = -1);

signals:
    void loginRealizado(const int &id, const QString &nome, const QString &clinica, const QString &cargo);

private slots:
    void on_btnEnt_clicked();
    void on_btnMostrar_clicked();
    void on_btnCancelar_clicked();

private:
    Ui::janela_entrar *ui;
    Conexao *conexao;

    bool logadoJanela;
    QString nome, clinica, cargo;
    int id;
};

#endif // JANELA_ENTRAR_H
