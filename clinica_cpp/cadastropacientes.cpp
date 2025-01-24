#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"
#include <QMessageBox>

// DEFINIÇÃO DO CONSTRUTOR DA CLASSE CADASTROPACIENTE

cadastroPacientes::cadastroPacientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroPacientes)
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
        "QPushButton#btnCancelarPac { background-color: #d0d0d0; }"
        "QPushButton:hover { background-color: #c0c0c0; }"
        "QPushButton#btnCancelarPac:hover { background-color: #b0b0b0; }"
        "QPushButton#btnCadastrarPac { background-color: #6db0ec; }"
        "QPushButton#btnCadastrarPac:hover { background-color: #5a9bd8; }"
        );

}

// FIM


// DEFINIÇÃO DO DESTRUTOR DA CLASSE CADASTROPACIENTE

cadastroPacientes::~cadastroPacientes()
{
    delete ui;
}

// FIM



// DEFINIÇÃO DO METODO CADASTRAR PACIENCE SELECIONADO

void cadastroPacientes::on_btnCadastrarPac_clicked()
{
    // Recupera os dados dos campos da interface do usuário                                                         // OBTÉM OS DADOS DOS CAMPOS DA INTERFACE
    QString nom = ui->txtnome->text();                                                                                   
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString diagn = ui->txtDiagn->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();
    QString conven = ui->txtconvenio->text(); 

    // Cria um objeto Paciente com os dados recuperados                                                            // CRIA UM OBJETO PACIENTE COM OS DADOS RECUPERADOS
    Paciente paciente(nom, cpf, contat, emai, dataNascimento, conven, diagn);

    // Conecta o sinal pacienteCadastrado ao slot correspondente                                                   // CONECTA O SINAL PACIENTE CADASTRADO AO SLOT CORRESPONDENTE
    connect(&paciente, &Paciente::pacienteCadastrado, this, &cadastroPacientes::pacienteCadastrado);

    // Salva o objeto Paciente no banco de dados                                                                   // SALVA O OBJETO PACIENTE NO BANCO DE DADOS
    if (paciente.salvarNoBanco()) {
        QMessageBox::information(this, "", "Cadastro realizado");
        this->close();
    } else {
        QMessageBox::information(this, "ERRO", "Erro ao cadastrar paciente");
    }
}

// FIM


// DEFINIÇÃO DO METODO CANCELAR CADASTRO

void cadastroPacientes::on_btnCancelarPac_clicked()
{
    this->close();
}

// FIM

