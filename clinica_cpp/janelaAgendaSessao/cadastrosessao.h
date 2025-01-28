#ifndef CADASTROSESSAO_H
#define CADASTROSESSAO_H

#include <QDialog>
#include <QtSql>
#include <QTableWidget>
#include <QMessageBox>

#include "../janelaPrincipal/mainwindow.h"

class MainWindow;

namespace Ui {
class cadastroSessao;
}

class cadastroSessao : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroSessao(MainWindow *mainWindow, const QString &modo = "", int idSessao = -1, QWidget *parent = nullptr);
    ~cadastroSessao();

    void setModo(const QString &modo);

private slots:

    // Método para cadastrar um novo paciente
    void on_btnCadastrarSes_clicked();

    // Método para cancelar o cadastro
    void on_btnCancelarSes_clicked();

    void on_pesquisarPacAg_textChanged(const QString &arg1);

    void redimensionarTable(QTableWidget* table);

    void setTabelaPacSes(QSqlQuery &query);

    void on_tw_paciente_ses_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

signals:
    void sessaoCadastrada(int idSessao);  // Sinal que enviará o ID da sessão cadastrada

    void sessaoEditada(int idSessao);

private:
    Ui::cadastroSessao *ui;

    MainWindow *m_mainWindow;

    QString tipoUso;

    int m_idSessao;
};

#endif // CADASTROSESSAO_H
