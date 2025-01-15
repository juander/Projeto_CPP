#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"
#include <QMessageBox>

cadastroPacientes::cadastroPacientes(QSqlDatabase db, QWidget *parent)
    : QDialog(parent)
    , bancoDeDados(db)
    , ui(new Ui::cadastroPacientes)
{
    ui->setupUi(this);

    if (!bancoDeDados.isOpen()) {
        qDebug() << "Banco de dados está fechado na nova janela!";
    } else {
        qDebug() << "Banco de dados acessível na nova janela!";
    }
}

cadastroPacientes::~cadastroPacientes()
{
    delete ui;
}

void cadastroPacientes::on_btnCadastrar_clicked()
{
    QString nom = ui->txtnome->text();
    QString idad = ui->txtidade->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();
    QString conven = ui->txtconvenio->text();

    QSqlQuery query;
    query.prepare("INSERT INTO tb_pacientes (nome, idade, contato, email, convenio_plano) "
                  "VALUES (:nome, :idade, :contato, :email, :convenio_plano)");

    query.bindValue(":nome", nom);
    query.bindValue(":idade", idad);
    query.bindValue(":contato", contat);
    query.bindValue(":email", emai);
    query.bindValue(":convenio_plano", conven);

    if (query.exec()) {
        QMessageBox::information(this, "", "Cadastro realizado");
        ui->txtnome->clear();
        ui->txtidade->clear();
        ui->txtcontato->clear();
        ui->txtemail->clear();
        ui->txtconvenio->clear();
        ui->txtnome->setFocus();
    } else {
        qDebug() << "Erro ao cadastrar:" << query.lastError().text();
    }
}
