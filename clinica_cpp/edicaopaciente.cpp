#include "edicaopaciente.h"
#include "ui_edicaopaciente.h"

// Criando globalmente
static int id;

edicaopaciente::edicaopaciente(QWidget *parent, int id_paciente)
    : QDialog(parent)
    , ui(new Ui::edicaopaciente)
{
    ui->setupUi(this);
    id = id_paciente;

    ui->txtID->setText(QString::number(id_paciente));

    // Realizando uma query que traz os elementos do banco
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE id="+QString::number(id));

    if(query.exec()){
        query.first();
        ui->txtnome->setText(query.value(1).toString());
        ui->txtCpf->setText(query.value(3).toString());
        ui->txtcontato->setText(query.value(4).toString());
        ui->txtemail->setText(query.value(5).toString());
        ui->txtconvenio->setText(query.value(6).toString());

        // Convertendo a string da data para QDate
        QDate date = QDate::fromString(query.value(7).toString(), "dd/MM/yyyy");
        ui->txtData->setDate(date);

    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao selecionar edição do paciente");
    }
}

edicaopaciente::~edicaopaciente()
{
    delete ui;
}

void edicaopaciente::on_editar_clicked()
{
    // Realizando a query que enviar os dados editados para o banco
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
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
    QString idString = QString::number(id); // Convertendo o ID para QString
    query.prepare("UPDATE tb_pacientes SET nome = :nome, idade = :idade, cpf = :cpf, contato = :contato, "
                  "email = :email, convenio_plano = :convenio_plano, data_nasc = :data_nasc WHERE id = :id");

    query.bindValue(":nome", nom);
    query.bindValue(":idade", ida);
    query.bindValue(":cpf", cpf);
    query.bindValue(":contato", contat);
    query.bindValue(":email", emai);
    query.bindValue(":convenio_plano", conven);
    query.bindValue(":data_nasc", nasc);
    query.bindValue(":id", idString);

    if(query.exec()){
        QMessageBox::information(this, "", "Edição realizada!");
        this->close();
    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao editar contato");
    }
}

void edicaopaciente::on_cancelarEdit_clicked()
{
    this->close();
}
