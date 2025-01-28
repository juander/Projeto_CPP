#include "cadastrocolaboradores.h"
#include "ui_cadastrocolaboradores.h"
#include <QMessageBox>

cadastroColaboradores::cadastroColaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroColaboradores)
{
    ui->setupUi(this);

    setWindowTitle("MEDICALSOFT");

}

cadastroColaboradores::~cadastroColaboradores()
{
    delete ui;
}

void cadastroColaboradores::on_btnCadastrarCol_clicked()
{
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString cargo = ui->txtcargo->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();

    Colaborador Colaborador(nom, cpf, contat, emai, dataNascimento, cargo);

    connect(&Colaborador, &Colaborador::colaboradorCadastrado, this, &cadastroColaboradores::colaboradorCadastrado);

    // Salvar no banco
    if (Colaborador.salvarNoBanco()) {
        QMessageBox::information(this, "", "Cadastro realizado");
        this->close();
    } else {
        QMessageBox::information(this, "", "Erro ao cadastrar colaborador");
    }
}

void cadastroColaboradores::on_btnCancelarCol_clicked()
{
    this->close();
}

