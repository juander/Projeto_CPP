#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"
#include <QMessageBox>

// DEFINIÇÃO DO CONSTRUTOR DA CLASSE CADASTROPACIENTE

cadastroPacientes::cadastroPacientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroPacientes)
{
    ui->setupUi(this);
}

// FIM


// DEFINIÇÃO DO DESTRUTOR DA CLASSE CADASRTROPACIENTE

cadastroPacientes::~cadastroPacientes()
{
    delete ui;
}

void cadastroPacientes::on_btnCadastrar_clicked()
{
    // Recupera os dados dos campos da interface do usuário                                                         // OBTÉM OS DADOS DOS CAMPOS DA INTERFACE
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString diagn = ui->txtDiagn->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();
    QString conven = ui->txtconvenio->text();

    // Cria um objeto Paciente com os dados recuperados
    Paciente paciente(nom, cpf, contat, emai, dataNascimento, conven, diagn);

    // Conecta o sinal pacienteCadastrado ao slot correspondente
    connect(&paciente, &Paciente::pacienteCadastrado, this, &cadastroPacientes::pacienteCadastrado);

    // Salva o objeto Paciente no banco de dados
    if (paciente.salvarNoBanco()) {
        QMessageBox::information(this, "", "Cadastro realizado");
        this->close();
    } else {
        QMessageBox::information(this, "ERRO", "Erro ao cadastrar paciente");                                      // Mensagem de erro
    }
}

void cadastroPacientes::on_btnCancelar_clicked()
{
    this->close();
}
