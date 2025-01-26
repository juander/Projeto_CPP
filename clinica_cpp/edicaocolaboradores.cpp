#include "edicaocolaboradores.h"
#include "ui_edicaocolaboradores.h"

// Criando globalmente
static int id;

edicaoColaboradores::edicaoColaboradores(QWidget *parent, int id_colaborador)
    : QDialog(parent)
    , ui(new Ui::edicaoColaboradores)
{
    ui->setupUi(this);

    setWindowTitle("MEDICALSOFT");

    this->setStyleSheet(
        "QDialog { background-color: #f0f0f0; border-radius: 10px; }"
        "QLabel { font-size: 14pt; color: #333; }"
        "QLineEdit, QDateEdit { border: 1px solid #ccc; border-radius: 5px; font-size: 12pt; background-color: #fff; color: #333; height: 30px; padding: 5px; }"
        "QLineEdit { padding-left: 5px; }"
        "QDateEdit::up-button, QDateEdit::down-button { background-color: #e0e0e0; border: none; width: 16px; height: 16px; padding: 0px; }"
        "QDateEdit::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QDateEdit::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QDateEdit::up-arrow { image: url(:/icons/up-arrow.png); width: 12px; height: 12px; }"
        "QDateEdit::down-arrow { image: url(:/icons/down-arrow.png); width: 12px; height: 12px; }"
        "QPushButton { background-color: #e0e0e0; color: #333; border: 1px solid #ccc; border-radius: 5px; padding: 5px 10px; font-size: 12pt; }"
        "QPushButton#cancelarEdit, QPushButton#btnCancelarPac { background-color: #d0d0d0; }"
        "QPushButton:hover { background-color: #c0c0c0; }"
        "QPushButton#cancelarEdit:hover, QPushButton#btnCancelarPac:hover { background-color: #b0b0b0; }"
        "QPushButton#editar, QPushButton#btnCadastrarPac { background-color: #6db0ec; }"
        "QPushButton#editar:hover, QPushButton#btnCadastrarPac:hover { background-color: #5a9bd8; }"
        );

    id = id_colaborador;

    // Realizando uma query que traz os elementos do banco
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_colaboradores WHERE id="+QString::number(id));

    if(query.exec()){
        query.first();
        ui->txtnome->setText(query.value(1).toString());
        ui->txtCpf->setText(query.value(3).toString());
        ui->txtcargo->setText(query.value(4).toString());
        ui->txtcontato->setText(query.value(5).toString());
        ui->txtemail->setText(query.value(6).toString());

        // Convertendo a string da data para QDate
        QDate date = QDate::fromString(query.value(7).toString(), "dd/MM/yyyy");
        ui->txtData->setDate(date);

    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao selecionar edição do colaborador");
    }
}

edicaoColaboradores::~edicaoColaboradores()
{
    delete ui;
}

void edicaoColaboradores::on_editar_clicked()
{
    // Realizando a query que enviar os dados editados para o banco
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString cargo = ui->txtcargo->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();

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
    query.prepare("UPDATE tb_colaboradores SET nome = :nome, idade = :idade, cpf = :cpf, cargo = :cargo, contato = :contato, "
                  "email = :email, data_nasc = :data_nasc WHERE id = :id");

    query.bindValue(":nome", nom);
    query.bindValue(":idade", ida);
    query.bindValue(":cpf", cpf);
    query.bindValue(":cargo", cargo);
    query.bindValue(":contato", contat);
    query.bindValue(":email", emai);
    query.bindValue(":data_nasc", nasc);
    query.bindValue(":id", idString);

    if(query.exec()){
        QMessageBox::information(this, "", "Edição realizada!");
        this->close();
    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao editar colaborador");
    }
}

void edicaoColaboradores::on_cancelarEdit_clicked()
{
    this->close();
}

