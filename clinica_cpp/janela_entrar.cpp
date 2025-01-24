#include "janela_entrar.h"
#include "ui_janela_entrar.h"
#include <QMessageBox>
#include <QDebug>

janela_entrar::janela_entrar(QWidget *parent, Conexao *conexao)
    : QDialog(parent)
    , ui(new Ui::janela_entrar)
    , conexao(conexao)
    , logadoJanela(false) // Inicializa como falso
{
    ui->setupUi(this);

    // Ajuste de estilo para a janela de login
    this->setStyleSheet(
        "QDialog {"
        "    background-color: #f0f0f0;"
        "    border-radius: 10px;"
        "}"
        "QLabel {"
        "    font-size: 14pt;"
        "    color: #333;"
        "}"
        "QLineEdit {"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 12pt;"
        "}"
        "QPushButton {"
        "    background-color: #e0e0e0;"
        "    color: #333;"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "    padding: 2px;"
        "    font-size: 12pt;"
        "}"
        "QPushButton#btnCancelar {"
        "    background-color: #d0d0d0;"
        "}"
        "QPushButton:hover {"
        "    background-color: #c0c0c0;"
        "}"
        "QPushButton#btnCancelar:hover {"
        "    background-color: #b0b0b0;"
        "}"
        "QPushButton#btnMostrar {"
        "    background-color: transparent;"
        "    border: none;"
        "}"
    );

    // Ajuste de ícones
    ui->btnMostrar->setIcon(QIcon(":/icons/Hide.png"));
    ui->btnMostrar->setIconSize(QSize(24, 24));
}

janela_entrar::~janela_entrar() {
    delete ui;
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

    QString nomeDigitado = ui->txtnome->text();
    QString senhaDigitada = ui->txtsenha->text();
    QSqlQuery query;

    query.prepare("SELECT * FROM tb_usuarios WHERE nome = :nome");
    query.bindValue(":nome", nomeDigitado);

    if (query.exec() && query.first()) {
        if (query.value("senha").toString() == senhaDigitada) {
            logadoJanela = true;
            id = query.value("id").toInt();
            nome = query.value("nome").toString();
            clinica = query.value("clinica").toString();
            cargo = query.value("cargo").toString();

            emit loginRealizado(id, nome, clinica, cargo); // Emite o sinal com os dados do usuário
            close();
        } else {
            QMessageBox::warning(this, " ", "Senha incorreta.");
        }
    } else {
        QMessageBox::warning(this, " ", "Usuário não encontrado.");
    }
}

void janela_entrar::on_btnCancelar_clicked() {
    logadoJanela = false;
    close();
}

void janela_entrar::on_btnMostrar_clicked() {
    if (ui->txtsenha->echoMode() == QLineEdit::Password) {
        ui->txtsenha->setEchoMode(QLineEdit::Normal);
        ui->btnMostrar->setIcon(QIcon(":/icons/Eye.png")); // Ícone de olho aberto
    } else {
        ui->txtsenha->setEchoMode(QLineEdit::Password);
        ui->btnMostrar->setIcon(QIcon(":/icons/Hide.png")); // Ícone de olho fechado
    }
}
