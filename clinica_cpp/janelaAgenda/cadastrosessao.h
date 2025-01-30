#ifndef CADASTROSESSAO_H
#define CADASTROSESSAO_H

#include <QDialog>
#include <QtSql>
#include <QTableWidget>
#include <QMessageBox>

#include "../janelaPrincipal/mainwindow.h"                                                                                   // Inclui o cabeçalho da janela principal

class MainWindow;                                                                                                            // Declaração antecipada da classe MainWindow

namespace Ui {                                                                                                               // Namespace Ui
class cadastroSessao;                                                                                                        // Declaração antecipada da classe cadastroSessao
}

class cadastroSessao : public QDialog                                                                                        // Declaração da classe cadastroSessao que herda de QDialog
{
    Q_OBJECT                                                                                                                 // Macro Q_OBJECT para sinal e slot

public:                                                                                                                      // Membros públicos
    explicit cadastroSessao(MainWindow *mainWindow, const QString &modo = "", int idSessao = -1, QWidget *parent = nullptr); // Construtor
    ~cadastroSessao();                                                                                                       // Destrutor

    void setModo(const QString &modo);                                                                                       // Define o modo (Cadastrar ou Editar)

    void setIdSessao(int id = -1);                                                                                           // Define o ID da sessão
    int getIdSessao() const;                                                                                                 // Retorna o ID da sessão

    void setTipoUso(const QString &modo);                                                                                    // Define o tipo de uso
    QString getTipoUso() const;                                                                                              // Retorna o tipo de uso

    void setConexaoJanelaPrincipal(MainWindow *mainWindow);                                                                  // Define a conexão com a janela principal
    MainWindow* getMainWindow() const;                                                                                       // Retorna a conexão com a janela principal

private slots:                                                                                                               // Slots privados
    void on_btnCadastrarSes_clicked();                                                                                       // Método para cadastrar uma nova sessão
    void on_btnCancelarSes_clicked();                                                                                        // Método para cancelar o cadastro
    void on_pesquisarPacAg_textChanged(const QString &arg1);                                                                 // Método para pesquisar pacientes
    void redimensionarTable(QTableWidget* table);                                                                            // Método para redimensionar a tabela
    void setTabelaPacSes(QSqlQuery &query);                                                                                  // Método para definir a tabela de pacientes
    void on_tw_paciente_ses_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);      // Método para detectar mudança de célula na tabela

signals:                                                                                                                     // Sinais
    void sessaoCadastrada();                                                                                                 // Sinal emitido quando uma sessão é cadastrada
    void sessaoEditada();                                                                                                    // Sinal emitido quando uma sessão é editada

private:                                                                                                                     // Membros privados
    Ui::cadastroSessao *ui;                                                                                                  // Ponteiro para a interface do usuário
    MainWindow *m_mainWindow;                                                                                                // Conexão com a janela principal
    QString tipoUso;                                                                                                         // Tipo de uso (Cadastrar ou Editar)
    int m_idSessao;                                                                                                          // ID da sessão
};

#endif // CADASTROSESSAO_H
