#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QCommandLinkButton>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

#include "cadastropacientes.h"
#include "edicaopaciente.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAgenda_clicked();
    void on_btnAtendimento_clicked();
    void on_btnPacientes_clicked();
    void on_btnProfissionais_clicked();
    void on_btnFornecedores_clicked();
    void on_btnRelatorios_clicked();

    void adicionarPacienteNaTabela(int id = 0);
    void on_btnCadastro_clicked();

    void on_btnApagarPac_clicked();

    void on_btnEditarPac_clicked();

    void on_btnPesquisarPac_clicked();

    void setTabelaPacientes(QSqlQuery &query);

private:
    Ui::MainWindow *ui;
    QSqlDatabase bancoDeDados;
};
#endif // MAINWINDOW_H
