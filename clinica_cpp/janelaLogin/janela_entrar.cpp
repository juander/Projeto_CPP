#include "janela_entrar.h"
#include "janelaLogin/ui_janela_entrar.h"

#include <QMessageBox>
#include <QDebug>

janela_entrar::janela_entrar(QWidget *parent, Conexao *conexao)
    : QDialog(parent)
    , ui(new Ui::janela_entrar)
    , conexao(conexao)
    , logadoJanela(false)                                                                  // Inicializa como falso
{
    ui->setupUi(this);

    ui->btnMostrar->setIcon(QIcon(":/icons/Hide.png"));                                    // Ajuste de ícones
    ui->btnMostrar->setIconSize(QSize(24, 24));
}

janela_entrar::~janela_entrar() {
    delete ui;                                                                             // Destrói a interface do usuário
}

bool janela_entrar::getLogadoJanela()
{
    return logadoJanela;                                                                   // Retorna o estado de login
}

QString janela_entrar::getNome()
{
    return nome;                                                                           // Retorna o nome do usuário
}

QString janela_entrar::getClinica()
{
    return clinica;                                                                        // Retorna a clínica do usuário
}

QString janela_entrar::getCargo()
{
    return cargo;                                                                          // Retorna o cargo do usuário
}

int janela_entrar::getId()
{
    return id;                                                                             // Retorna o ID do usuário
}

void janela_entrar::setLogadoJanela(bool login)
{
    logadoJanela = login;                                                                  // Define o estado de login
}

void janela_entrar::setNome(QString nom)
{
    nome = nom;                                                                            // Define o nome do usuário
}

void janela_entrar::setClinica(QString clin)
{
    clinica = clin;                                                                        // Define a clínica do usuário
}

void janela_entrar::setCargo(QString carg)
{
    cargo = carg;                                                                          // Define o cargo do usuário
}

void janela_entrar::setId(int codigo)
{
    id = codigo;                                                                           // Define o ID do usuário
}

void janela_entrar::on_btnEnt_clicked() {
    if (ui->txtnome->text().isEmpty() || ui->txtsenha->text().isEmpty()) {
        QMessageBox::warning(this, " ", "Preencha todos os campos!");
        return;
    }

    if (!conexao || !conexao->abrir()) {
        QMessageBox::critical(this, " ", "Erro ao abrir o banco de dados.");
        return;
    }

    QString loginDigitado = ui->txtnome->text();
    QString senhaDigitada = ui->txtsenha->text();
    QSqlQuery query;

    query.prepare("SELECT * FROM tb_usuarios WHERE login = :login");
    query.bindValue(":login", loginDigitado);                                              // Prepara a query para selecionar o usuário

    if (query.exec() && query.first()) {
        if (query.value("senha").toString() == senhaDigitada) {
            setLogadoJanela(true);
            setId(query.value("id").toInt());
            setNome(query.value("nome").toString());
            setClinica(query.value("clinica").toString());
            setCargo(query.value("cargo").toString());

            emit loginRealizado(getId(), getNome(), getClinica(), getCargo());             // Emite o sinal com os dados do usuário
            close();
        } else {
            QMessageBox::warning(this, " ", "Senha incorreta.");
        }
    } else {
        QMessageBox::warning(this, " ", "Usuário não encontrado.");
    }
}

void janela_entrar::on_btnCancelar_clicked() {
    setLogadoJanela(false);                                                                // Define o estado de login como falso
    close();                                                                               // Fecha a janela
}

void janela_entrar::on_btnMostrar_clicked() {
    if (ui->txtsenha->echoMode() == QLineEdit::Password) {
        ui->txtsenha->setEchoMode(QLineEdit::Normal);
        ui->btnMostrar->setIcon(QIcon(":/icons/Eye.png"));                                 // Ícone de olho aberto
    } else {
        ui->txtsenha->setEchoMode(QLineEdit::Password);
        ui->btnMostrar->setIcon(QIcon(":/icons/Hide.png"));                                // Ícone de olho fechado
    }
}
