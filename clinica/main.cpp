#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <vector>
#include "clinica.h"
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget janela;
    QVBoxLayout layout(&janela);

    QPushButton btnCadastrar("Cadastrar Paciente");
    QPushButton btnExibir("Exibir Pacientes");

    vector<Paciente> pacientes;

    QObject::connect(&btnCadastrar, &QPushButton::clicked, [&]() {
        bool ok;
        QString nome = QInputDialog::getText(&janela, "Cadastrar Paciente", "Nome:", QLineEdit::Normal, "", &ok);
        if (!ok || nome.isEmpty()) return;

        int idade = QInputDialog::getInt(&janela, "Cadastrar Paciente", "Idade:", 0, 0, 150, 1, &ok);
        if (!ok) return;

        QString diagnostico = QInputDialog::getText(&janela, "Cadastrar Paciente", "Diagnóstico:", QLineEdit::Normal, "", &ok);
        if (!ok || diagnostico.isEmpty()) return;

        pacientes.emplace_back(nome.toStdString(), idade, diagnostico.toStdString());
        QMessageBox::information(&janela, "Cadastro", "Paciente cadastrado!");
    });

    QObject::connect(&btnExibir, &QPushButton::clicked, [&]() {
        QString lista;
        for (const auto& paciente : pacientes) {
            lista += QString::fromStdString(paciente.getInfo()) + "\n";
        }
        QMessageBox::information(&janela, "Lista de Pacientes", lista);
    });

    layout.addWidget(&btnCadastrar);
    layout.addWidget(&btnExibir);

    janela.setLayout(&layout);
    janela.setWindowTitle("Sistema de Clínica");
    janela.show();

    return app.exec();
}
