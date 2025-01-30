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

    // Métodos get e set
    void setIdSessao(int id = -1);

    int getIdSessao() const;

    void setTipoUso(const QString &modo);

    QString getTipoUso() const;

    // Métodos get e set para m_mainWindow
    void setConexaoJanelaPrincipal(MainWindow *mainWindow);

    MainWindow* getMainWindow() const;


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
    void sessaoCadastrada();

    void sessaoEditada();

private:
    Ui::cadastroSessao *ui;

    MainWindow *m_mainWindow;

    QString tipoUso;

    int m_idSessao;
};

#endif // CADASTROSESSAO_H
