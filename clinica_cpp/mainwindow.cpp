#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

using namespace std;

Pessoa::Pessoa(string n, int i) : nome(n), idade(i) {}

string Pessoa::getNome() const {
    return nome;
}

int Pessoa::getIdade() const {
    return idade;
}

Paciente::Paciente(string n, int i, string d) : Pessoa(n, i), diagnostico(d) {}

string Paciente::getDiagnostico() const {
    return diagnostico;
}

string Paciente::getInfo() const {
    return "Nome: " + nome + ", Idade: " + to_string(idade) + ", Diagnóstico: " + diagnostico;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectando os botões às funções de slot
    connect(ui->btnCadastrar, &QPushButton::clicked, this, &MainWindow::on_btnCadastrar_clicked);
    connect(ui->btnExibir, &QPushButton::clicked, this, &MainWindow::on_btnExibir_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCadastrar_clicked()
{
    bool ok;
    QString nome = QInputDialog::getText(this, "Cadastrar Paciente", "Nome:", QLineEdit::Normal, "", &ok);
    if (!ok || nome.isEmpty()) return;

    int idade = QInputDialog::getInt(this, "Cadastrar Paciente", "Idade:", 0, 0, 150, 1, &ok);
    if (!ok) return;

    QString diagnostico = QInputDialog::getText(this, "Cadastrar Paciente", "Diagnóstico:", QLineEdit::Normal, "", &ok);
    if (!ok || diagnostico.isEmpty()) return;

    pacientes.emplace_back(nome.toStdString(), idade, diagnostico.toStdString());
    QMessageBox::information(this, "Cadastro", "Paciente cadastrado!");
}


void MainWindow::on_btnExibir_clicked()
{
    QString lista;
    for (const auto& paciente : pacientes) {
        lista += QString::fromStdString(paciente.getInfo()) + "\n";
    }
    QMessageBox::information(this, "Lista de Pacientes", lista);
}


void MainWindow::on_pushButton_clicked()
{
    pag2 = new registerwindow(this);
    pag2->exec();
}

