#include "janela_entrar.h"
#include "ui_janela_entrar.h"
#include <QMessageBox>

janela_entrar::janela_entrar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janela_entrar)
{
    ui->setupUi(this);
    logado = false;
}

janela_entrar::~janela_entrar()
{
    delete ui;
}

void janela_entrar::on_btnEntrar_clicked()
{
    if(!conex.abrir()){
        qDebug() << "Erro ao abrir o banco de dados:";                           // CONFERINDO SE O BANCO FOI CONECTADO
    } else {
        qDebug() << "Banco de dados conectado com sucesso!";
        QString nome, senha;
        nome = ui->txtnome->text();
        senha = ui->txtsenha->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_usuarios WHERE nome = :nome");
        query.bindValue(":nome", nome);
        if(query.exec()){
            if(query.first()){
                if(query.value(2) == senha){
                    logado = true;
                    conex.fechar();
                    close();
                } else {
                    QMessageBox::warning(this, " ", "Senha incorreta");
                }
            } else {
                QMessageBox::warning(this, " ", "Usuário não encontrado");
            }
        } else {
            QMessageBox::warning(this, " ", "Falha no Login");
        }
    }
}

void janela_entrar::on_btnMostrar_clicked()
{
    if(ui->txtsenha->echoMode() == QLineEdit::Password){
        ui->txtsenha->setEchoMode(QLineEdit::Normal);
        ui->btnMostrar->setIcon(QIcon(":/icons/Eye.png")); // Ícone de olho aberto
    } else {
        ui->txtsenha->setEchoMode(QLineEdit::Password);
        ui->btnMostrar->setIcon(QIcon(":/icons/Hide.png")); // Ícone de olho com risco
    }
}