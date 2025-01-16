#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"
#include <QMessageBox>

cadastroPacientes::cadastroPacientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroPacientes)
{
    ui->setupUi(this);
}

cadastroPacientes::~cadastroPacientes()
{
    delete ui;
}

void cadastroPacientes::on_btnCadastrar_clicked()
{
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString diagn = ui->txtDiagn->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();
    QString conven = ui->txtconvenio->text();

    Paciente paciente(nom, cpf, contat, emai, dataNascimento, conven, diagn);

    connect(&paciente, &Paciente::pacienteCadastrado, this, &cadastroPacientes::pacienteCadastrado);

    // Salvar no banco
    if (paciente.salvarNoBanco()) {
        QMessageBox::information(this, "", "Cadastro realizado");
        this->close();
    } else {
        QMessageBox::information(this, "ERRO", "Erro ao cadastrar paciente");
    }
}

void cadastroPacientes::on_btnCancelar_clicked()
{
    this->close();
}
