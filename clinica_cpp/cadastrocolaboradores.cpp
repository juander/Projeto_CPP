#include "cadastrocolaboradores.h"
#include "ui_cadastrocolaboradores.h"
#include <QMessageBox>

cadastroColaboradores::cadastroColaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroColaboradores)
{
    ui->setupUi(this);

    setWindowTitle("MEDICALSOFT");

    this->setStyleSheet(
        "QDialog { background-color: #f0f0f0; border-radius: 10px; }"
        "QLabel { font-size: 14pt; color: #333; }"
        "QLineEdit, QDateEdit { border: 1px solid #ccc; border-radius: 5px; font-size: 12pt; background-color: #fff; color: #333; height: 30px; }"
        "QDateEdit { padding-left: 8px; }"
        "QDateEdit::up-button, QDateEdit::down-button { background-color: #e0e0e0; border: none; width: 16px; height: 16px; padding: 0px; }"
        "QDateEdit::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QDateEdit::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QDateEdit::up-arrow, QDateEdit::down-arrow { image: url(:/icons/up-arrow.png); width: 8px; height: 8px; }"
        "QPushButton { background-color: #e0e0e0; color: #333; border: 1px solid #ccc; border-radius: 5px; padding: 5px 10px; font-size: 12pt; }"
        "QPushButton#btnCancelar, QPushButton#btnCancelarPac, QPushButton#btnCancelarCol { background-color: #d0d0d0; }"
        "QPushButton:hover { background-color: #c0c0c0; }"
        "QPushButton#btnCancelar:hover, QPushButton#btnCancelarPac:hover, QPushButton#btnCancelarCol:hover { background-color: #b0b0b0; }"
        "QPushButton#btnMostrar { background-color: transparent; border: none; }"
        "QPushButton#btnEnt, QPushButton#editar, QPushButton#btnCadastrarPac, QPushButton#btnCadastrarCol { background-color: #6db0ec; }"
        "QPushButton#btnEnt:hover, QPushButton#editar:hover, QPushButton#btnCadastrarPac:hover, QPushButton#btnCadastrarCol:hover { background-color: #5a9bd8; }"
        );

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

