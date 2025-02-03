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

    bool getLogado() const;                                                                                  // Retorna o estado de login
    QString getNomeUsuario() const;                                                                          // Retorna o nome do usuário
    QString getClinica() const;                                                                              // Retorna a clínica do usuário
    QString getCargo() const;                                                                                // Retorna o cargo do usuário
    int getIdUsuario() const;                                                                                // Retorna o ID do usuário
    int getIdSessao() const;                                                                                 // Retorna o ID da sessão

    void setLogado(bool login = false);                                                                      // Define o estado de login
    void setNomeUsuario(QString nome = nullptr);                                                             // Define o nome do usuário
    void setClinica(QString clin = nullptr);                                                                 // Define a clínica do usuário
    void setCargo(QString carg = nullptr);                                                                   // Define o cargo do usuário
    void setIdUsuario(int Id = -1);                                                                          // Define o ID do usuário
    void setIdSessao(int Id = -1);                                                                           // Define o ID da sessão

    void setPaletaCor(QApplication &app);                                                                    // Método para setar a paleta de cores do sistema para claro em qualquer dispositivo
    void janelaFormatada();                                                                                  // Método para formatar a página
    void redimensionarTable(QTableWidget* table);                                                            // Método para redimensionar as tabelas automaticamente

    void resetButtonStyles();                                                                                // Método para resetar os estilos dos botões
    void setButtonHighlight(QPushButton *botao);                                                             // Destaca o botão clicado
    void setLayoutEntrar();                                                                                  // Método para configurar o layout de entrada
    void setLayoutSair();                                                                                    // Método para configurar o layout de saída
    
private slots:
    void abrirPdf(const QString &link);                                                                      // Método para abrir um PDF

    void usuarioEntrou();                                                                                    // Método para tratar a entrada do usuário
    void usuarioSaiu();                                                                                      // Método para tratar a saída do usuário
    void on_btnEntrar_clicked();                                                                             // Método para tratar o clique no botão de entrar

    void on_btnInicio_clicked();                                                                             // Método para trocar para a página de início
    void on_btnAgenda_clicked();                                                                             // Método para trocar para a página de agenda
    void on_btnAtendimento_clicked();                                                                        // Método para trocar para a página de atendimento
    void on_btnPacientes_clicked();                                                                          // Método para trocar para a página de pacientes
    void on_btnColaboradores_clicked();                                                                      // Método para trocar para a página de colaboradores
    void on_btnEstoque_clicked();                                                                            // Método para trocar para a página de estoque
    void on_btnRelatorios_clicked();                                                                         // Método para trocar para a página de relatórios

    void setAgenda(QSqlQuery &query);                                                                        // Método para configurar a agenda
    void filtrarAgenda();                                                                                    // Método para filtrar a agenda
    void on_checkDataAgenda_checkStateChanged(const Qt::CheckState &arg1);                                   // Método para tratar a mudança de estado do checkbox de data da agenda
    void on_checkMinhaAgenda_stateChanged(int arg1);                                                         // Método para tratar a mudança de estado do checkbox de minha agenda
    void on_comboBoxAgenda_currentTextChanged(const QString &arg1);                                          // Método para tratar a mudança de texto da combobox de agenda
    void on_comboBoxStatusAgenda_currentTextChanged(const QString &arg1);                                    // Método para tratar a mudança de texto da combobox de status da agenda
    void on_lineEditAgenda_textChanged(const QString &arg1);                                                 // Método para tratar a mudança de texto do line edit de agenda
    void on_calendarioAgenda_clicked(const QDate &date);                                                     // Método para tratar o clique no calendário da agenda
    void on_btnAgendar_clicked();                                                                            // Método para tratar o clique no botão de agendar
    void adicionarSessaoNaTabela();                                                                          // Método para adicionar uma sessão na tabela
    void on_btnEditarAgenda_clicked();                                                                       // Método para tratar o clique no botão de editar agenda
    void atualizarSessaoNaTabela();                                                                          // Método para atualizar a sessão na tabela
    void on_tw_agenda_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn); // Método para tratar a mudança de célula na tabela de agenda
    void on_btnVerRelatorio_clicked();                                                                       // Método para tratar o clique no botão de ver relatório

    void setTabelaAtendimento(QSqlQuery &query);                                                             // Método para configurar a tabela de atendimento
    void on_comboBoxAtender_currentIndexChanged(int index);                                                  // Método para tratar a mudança de índice da combobox de atendimento
    void atualizarTabelaAtendimento();                                                                       // Método para atualizar a tabela de atendimento
    void on_lineEditAtendimento_textChanged(const QString &arg1);                                            // Método para tratar a mudança de texto do line edit de atendimento
    void on_checkHoje_checkStateChanged(const Qt::CheckState &arg1);                                         // Método para tratar a mudança de estado do checkbox de hoje
    void on_tw_atendimento_cellClicked(int row, int column);                                                 // Método para tratar o clique na célula da tabela de atendimento
    void on_btnSalvar_clicked();                                                                             // Método para tratar o clique no botão de salvar
    void on_btnDesfazer_clicked();                                                                           // Método para tratar o clique no botão de desfazer

    void setTabelaPacientes(QSqlQuery &query);                                                               // Método para configurar a tabela de pacientes
    void adicionarPacienteNaTabela(int id = 0);                                                              // Método para adicionar um paciente na tabela
    void on_btnCadastroPac_clicked();                                                                        // Método para cadastrar um novo paciente
    void on_btnApagarPac_clicked();                                                                          // Método para apagar um paciente selecionado
    void on_btnEditarPac_clicked();                                                                          // Método para editar um paciente selecionado
    void on_linePesquisaPac_textChanged(const QString &arg1);                                                // Método para pesquisar pacientes pelo nome

    void setTabelaColaboradores(QSqlQuery &query);                                                           // Método para configurar a tabela de colaboradores
    void adicionarColaboradorNaTabela(int id = 0);                                                           // Método para adicionar um colaborador na tabela
    void on_btnCadastroCol_clicked();                                                                        // Método para cadastrar um novo colaborador
    void on_btnApagarCol_clicked();                                                                          // Método para apagar um colaborador
    void on_btnEditarCol_clicked();                                                                          // Método para editar um colaborador
    void on_linePesquisaCol_textChanged(const QString &arg1);                                                // Método para pesquisar colaboradores pelo nome

    void setTabelaEstoque(QSqlQuery &query);                                                                 // Método para configurar a tabela de estoque
    void on_lineEditEstoque_textChanged(const QString &arg1);                                                // Método para tratar a mudança de texto do line edit de estoque
    void on_radioProduto_toggled(bool checked);                                                              // Método para tratar a mudança de estado do radio button de produto
    void on_tw_estoque_cellClicked(int row, int column);                                                     // Método para tratar o clique na célula da tabela de estoque
    void on_btnDesfazerEstoque_clicked();                                                                    // Método para tratar o clique no botão de desfazer estoque
    void on_btnAtualizar_clicked();                                                                          // Método para tratar o clique no botão de atualizar
    void on_btnAdicionar_clicked();                                                                          // Método para tratar o clique no botão de adicionar
    void on_btnApagar_clicked();                                                                             // Método para tratar o clique no botão de apagar

    void setTreeWidget(QTreeWidget *treeWidget);                                                             // Método para configurar o tree widget
    void carregarRelatorios(int* idSessao = nullptr);                                                        // Método para carregar relatórios
    void on_trw_atendimentos_itemClicked(QTreeWidgetItem *item, int column);                                 // Método para tratar o clique no item do tree widget de atendimentos

private:
    Ui::MainWindow *ui;

    QPushButton *botaoAtivo = nullptr;                                                                       // Armazena o botão atualmente selecionado
    Conexao conexao;                                                                                         // Conexão com o banco de dados
    bool logado;                                                                                             // Estado de login
    QString nome_usuario, clinica_usuario, cargo_usuario;                                                    // Informações do usuário
    int id_usuario;                                                                                          // ID do usuário
    int idSessaoSelecionada;                                                                                 // ID da sessão selecionada
};

#endif // MAINWINDOW_H
