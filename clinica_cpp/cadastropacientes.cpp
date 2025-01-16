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

    // Calculando idade
    QDate hoje = QDate::currentDate();
    int idad = hoje.year() - dataNascimento.year();

    // Se ainda não fez aniversário no ano atual, subtrai 1
    if ((hoje.month() < dataNascimento.month()) ||
        (hoje.month() == dataNascimento.month() && hoje.day() < dataNascimento.day())) {
        idad--;
    }

    QString ida = QString::number(idad);

    // Transformando a data em string para envio pro banco de dados
    QString nasc = dataNascimento.toString("dd/MM/yyyy");

    // Fazendo a query para enviar os dados para o banco
    QSqlQuery query;
    query.prepare("INSERT INTO tb_pacientes (nome, idade, cpf, diagnostico_pre = :diagnostico_pre, contato, email, convenio_plano, data_nasc) "
                  "VALUES (:nome, :idade, :cpf, :contato, :email, :convenio_plano, :data_nasc)");

    query.bindValue(":nome", nom);
    query.bindValue(":idade", ida);
    query.bindValue(":cpf", cpf);
    query.bindValue(":diagnostico_pre", diagn);
    query.bindValue(":contato", contat);
    query.bindValue(":email", emai);
    query.bindValue(":convenio_plano", conven);
    query.bindValue(":data_nasc", nasc);

    // Exibindo um pop-up de confirmação e ajustando os campos após o cadastro
    if (query.exec()) {
        int Id_novo = query.lastInsertId().toInt();  // Obtendo o último ID inserido
        emit pacienteCadastrado(Id_novo);            // Emitindo um sinal para a MainWindow
        QMessageBox::information(this, "", "Cadastro realizado");
        this->close();
    } else {
        qDebug() << "Erro ao cadastrar:" << query.lastError().text();
    }
}

void cadastroPacientes::on_btnCancelar_clicked()
{
    this->close();
}
