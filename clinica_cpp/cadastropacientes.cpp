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

