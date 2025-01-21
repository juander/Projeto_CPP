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
