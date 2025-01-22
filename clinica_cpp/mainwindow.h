#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QCommandLinkButton>
#include <QStyleFactory>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QMovie>

#include "Conexao.h"

#include "janela_entrar.h"

#include "cadastropacientes.h"
#include "cadastrocolaboradores.h"

#include "edicaopaciente.h"
#include "edicaocolaboradores.h"

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

    void setPaletaCor(QApplication &app);                              // MÉTODO PARA SETAR A PALETA DE CORES DO SISTEMA PARA CLARO EM QUALQUER DISPOSITIVO

    void janelaFormatada();                                            // MÉTODO PARA FORMATAR A PÁGINA

private slots:

    // MÉTODOS DE LOGIN

    void usuarioEntrou();

    void usuarioSaiu();

    void on_btnEntrar_clicked();

    //////////////////////////////////////////////

    // MÉTODOS DA TROCA DE PÁGINAS


    void on_btnInicio_clicked();

    void on_btnAgenda_clicked();

    void on_btnAtendimento_clicked();

    void on_btnPacientes_clicked();

    void on_btnColaboradores_clicked();

    void on_btnFornecedores_clicked();

    void on_btnRelatorios_clicked();

    //////////////////////////////////////////////

    void setAgenda(QSqlQuery &query);                      // MÉTODOS DE AGENDAMENTO

    void on_checkMinhaAgenda_stateChanged(int arg1);

    void on_comboBoxAgenda_currentTextChanged(const QString &arg1);

    void on_lineEditAgenda_textChanged(const QString &arg1);

    void on_checkDataAgenda_stateChanged(int arg1);

    void on_calendarioAgenda_clicked(const QDate &date);

    void atualizarTabelaPorData();

    //////////////////////////////////////////////

    // Método para configurar a tabela de pacientes
    void setTabelaPacientes(QSqlQuery &query);

    // Método para adicionar um paciente na tabela
    void adicionarPacienteNaTabela(int id = 0);

    // Método para cadastrar um novo paciente               // MÉTODOS DO PACIENTE
    void on_btnCadastroPac_clicked();

    // Método para apagar um paciente selecionado
    void on_btnApagarPac_clicked();

    // Método para editar um paciente selecionado
    void on_btnEditarPac_clicked();

    // Método para pesquisar pacientes pelo nome
    void on_linePesquisaPac_textChanged(const QString &arg1);

    ///////////////////////////////////////////////

    // Método para configurar a tabela de colaboradores
    void setTabelaColaboradores(QSqlQuery &query);

    // Método para adicionar um paciente na tabela
    void adicionarColaboradorNaTabela(int id = 0);          // MÉTODOS DO COLABORADOR

    // Método para cadastrar um novo colaborador
    void on_btnCadastroCol_clicked();

    // Método para apagar um colaborador
    void on_btnApagarCol_clicked();

    // Método para editar um colaborador
    void on_btnEditarCol_clicked();

    void on_linePesquisaCol_textChanged(const QString &arg1);

    /////////////////////////////////////////////////

private:
    Ui::MainWindow *ui;

    void redimensionarTable(QTableWidget* table);           // MÉTODO PARA REDIMENSÃO DAS TABELAS AUTOMATICAMENTE

    void resetButtonStyles();                               // MÉTODO PARA RESETAR OS ESTILOS DOS BOTÕES

    // Conexão com o banco de dados
    Conexao conexao;

    // Estado de login e informações do usuário
    bool logado;                                               // Indica se o usuário está logado
    QString nome_usuario, clinica_usuario, cargo_usuario;      // Nome do usuário logado
    int id_usuario;

};

#endif // MAINWINDOW_H
