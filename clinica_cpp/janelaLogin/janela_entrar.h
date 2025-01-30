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
    explicit janela_entrar(QWidget *parent = nullptr, Conexao *conexao = nullptr);          // Construtor
    ~janela_entrar();                                                                       // Destrutor

    bool getLogadoJanela();                                                                 // Retorna o estado de login
    QString getNome();                                                                      // Retorna o nome do usuário
    QString getClinica();                                                                   // Retorna a clínica do usuário
    QString getCargo();                                                                     // Retorna o cargo do usuário
    int getId();                                                                            // Retorna o ID do usuário

    void setLogadoJanela(bool login = false);                                               // Define o estado de login
    void setNome(QString nom = nullptr);                                                    // Define o nome do usuário
    void setClinica(QString clin = nullptr);                                                // Define a clínica do usuário
    void setCargo(QString carg = nullptr);                                                  // Define o cargo do usuário
    void setId(int codigo = -1);                                                            // Define o ID do usuário

signals:
    void loginRealizado(const int &id, const QString &nome, const QString &clinica, const QString &cargo); // Sinal emitido quando o login é realizado

private slots:
    void on_btnEnt_clicked();                                                               // Método para tratar o clique no botão de entrar
    void on_btnMostrar_clicked();                                                           // Método para tratar o clique no botão de mostrar senha
    void on_btnCancelar_clicked();                                                          // Método para tratar o clique no botão de cancelar

private:
    Ui::janela_entrar *ui;
    Conexao *conexao;                                                                       // Conexão com o banco de dados

    bool logadoJanela;                                                                      // Estado de login
    QString nome, clinica, cargo;                                                           // Dados do usuário
    int id;                                                                                 // ID do usuário
};

#endif // JANELA_ENTRAR_H
