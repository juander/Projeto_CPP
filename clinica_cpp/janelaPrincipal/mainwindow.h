#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QCommandLinkButton>
#include <QStyleFactory>
#include <QDesktopServices>
#include <QUrl>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QTreeWidget>
#include <QToolButton>
#include <QSplitter>

#include "../classConexaoBanco/Conexao.h"

#include "../janelaLogin/janela_entrar.h"

#include "../janelaPacientes/cadastropacientes.h"
#include "../janelaColaboradores/cadastrocolaboradores.h"
#include "../janelaAgenda/cadastrosessao.h"

#include "../classPessoa/pessoa.h"

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

    ////////////////////////////////////////

    // MÉTODOS GET

    bool getLogado() const;

    QString getNomeUsuario() const;

    QString getClinica() const;

    QString getCargo() const;

    int getIdUsuario() const;

    int getIdSessao() const;

    ////////////////////////////////////////

    // MÉTODOS SET

    void setLogado(bool login = false);

    void setNomeUsuario(QString nome = nullptr);

    void setClinica(QString clin = nullptr);

    void setCargo(QString carg = nullptr);

    void setIdUsuario(int Id = -1);

    void setIdSessao(int Id = -1);

    ///////////////////////////////////////

    void setPaletaCor(QApplication &app);                              // MÉTODO PARA SETAR A PALETA DE CORES DO SISTEMA PARA CLARO EM QUALQUER DISPOSITIVO

    void janelaFormatada();                                            // MÉTODO PARA FORMATAR A PÁGINA

    void redimensionarTable(QTableWidget* table);                      // MÉTODO PARA REDIMENSÃO DAS TABELAS AUTOMATICAMENTE

private slots:

    void abrirPdf(const QString &link);

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

    void on_btnEstoque_clicked();

    void on_btnRelatorios_clicked();

    //////////////////////////////////////////////

    void setAgenda(QSqlQuery &query);

    void filtrarAgenda();

    void on_checkDataAgenda_checkStateChanged(const Qt::CheckState &arg1);

    void on_checkMinhaAgenda_stateChanged(int arg1);

    void on_comboBoxAgenda_currentTextChanged(const QString &arg1);

    void on_comboBoxStatusAgenda_currentTextChanged(const QString &arg1);

    void on_lineEditAgenda_textChanged(const QString &arg1);                             // MÉTODOS DE AGENDAMENTO

    void on_calendarioAgenda_clicked(const QDate &date);

    void on_btnAgendar_clicked();

    void adicionarSessaoNaTabela();

    void on_btnEditarAgenda_clicked();

    void atualizarSessaoNaTabela();

    void on_tw_agenda_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnVerRelatorio_clicked();


    //////////////////////////////////////////////

    void setTabelaAtendimento(QSqlQuery &query);

    void on_comboBoxAtender_currentIndexChanged(int index);

    void atualizarTabelaAtendimento();

    void on_lineEditAtendimento_textChanged(const QString &arg1);

    void on_checkHoje_checkStateChanged(const Qt::CheckState &arg1);            // MÉTODOS DE ATENDIMENTO

    void on_tw_atendimento_cellClicked(int row, int column);

    void on_btnSalvar_clicked();

    void on_btnDesfazer_clicked();

    /////////////////////////////////////////////

    // Método para configurar a tabela de pacientes
    void setTabelaPacientes(QSqlQuery &query);

    // Método para adicionar um paciente na tabela
    void adicionarPacienteNaTabela(int id = 0);

    // Método para cadastrar um novo paciente                                   // MÉTODOS DO PACIENTE
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
    void adicionarColaboradorNaTabela(int id = 0);                              // MÉTODOS DO COLABORADOR

    // Método para cadastrar um novo colaborador
    void on_btnCadastroCol_clicked();

    // Método para apagar um colaborador
    void on_btnApagarCol_clicked();

    // Método para editar um colaborador
    void on_btnEditarCol_clicked();

    void on_linePesquisaCol_textChanged(const QString &arg1);

    /////////////////////////////////////////////////

    void setTabelaEstoque(QSqlQuery &query);                                   // MÉTODOS DO ESTOQUE

    void on_lineEditEstoque_textChanged(const QString &arg1);

    void on_radioProduto_toggled(bool checked);

    void on_tw_estoque_cellClicked(int row, int column);

    void on_btnDesfazerEstoque_clicked();

    void on_btnAtualizar_clicked();

    void on_btnAdicionar_clicked();

    void on_btnApagar_clicked();

    //////////////////////////////////////////////////

    void setTreeWidget(QTreeWidget *treeWidget);

    void carregarRelatorios(int* idSessao = nullptr);                                    // MÉTODOS DOS RELATÓRIOS

    void on_trw_atendimentos_itemClicked(QTreeWidgetItem *item, int column);

private:

    Ui::MainWindow *ui;

    /////////////////////////////////////////////

    QPushButton *botaoAtivo = nullptr;                      // Armazena o botão atualmente selecionado

    void resetButtonStyles();                               // MÉTODO PARA RESETAR OS ESTILOS DOS BOTÕES

    void setButtonHighlight(QPushButton *botao);            // Destaca o botão clicado

    void setLayoutEntrar();

    void setLayoutSair();

    /////////////////////////////////////////////

    // Conexão com o banco de dados
    Conexao conexao;

    // Estado de login e informações do usuário
    bool logado;                                               // Indica se o usuário está logado

    QString nome_usuario, clinica_usuario, cargo_usuario;      // Nome do usuário logado

    int id_usuario;

    int idSessaoSelecionada;

};

#endif // MAINWINDOW_H
