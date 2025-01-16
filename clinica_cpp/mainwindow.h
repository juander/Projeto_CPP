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
#include "pessoa.h"

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
    // Métodos para trocar entre as abas
    void on_btnAgenda_clicked();
    void on_btnAtendimento_clicked();
    void on_btnPacientes_clicked();
    void on_btnProfissionais_clicked();
    void on_btnFornecedores_clicked();
    void on_btnRelatorios_clicked();

    // Método para adicionar um paciente na tabela
    void adicionarPacienteNaTabela(int id = 0);
    // Método para cadastrar um novo paciente
    void on_btnCadastro_clicked();
    // Método para apagar um paciente selecionado
    void on_btnApagarPac_clicked();
    // Método para editar um paciente selecionado
    void on_btnEditarPac_clicked();
    // Método para configurar a tabela de pacientes
    void setTabelaPacientes(QSqlQuery &query);
    // Método para pesquisar pacientes pelo nome
    void on_linePesquisa_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase bancoDeDados; // Objeto para conexão com o banco de dados
};

#endif // MAINWINDOW_H
