#include "cadastrocolaboradores.h"
#include "ui_cadastrocolaboradores.h"
#include <QMessageBox>
#include <QDebug>

cadastroColaboradores::cadastroColaboradores(QWidget *parent, const QString &modo, int id_colaborador)
    : QDialog(parent)
    , ui(new Ui::cadastroColaboradores)
{
    ui->setupUi(this);
    setIdColaborador(id_colaborador);                                                                                     // Define o ID do colaborador
    setModo(modo, getIdColaborador());                                                                                    // Define o modo (Cadastrar ou Editar)
}

cadastroColaboradores::~cadastroColaboradores()
{
    delete ui;                                                                                                            // Destrói a interface do usuário
}

void cadastroColaboradores::setIdColaborador(int id)
{
    idColaborador = id;                                                                                                   // Define o ID do colaborador
}

int cadastroColaboradores::getIdColaborador()
{
    return idColaborador;                                                                                                 // Retorna o ID do colaborador
}

void cadastroColaboradores::setModo(const QString &modo, int id_colaborador)
{
    tipoUso = modo;                                                                                                       // Define o tipo de uso

    if (modo == "Editar" && id_colaborador != -1) {
        ui->btnCadastrarCol->setText("Salvar Alterações");                                                                // Altera o texto do botão para "Salvar Alterações"

        QSqlQuery query;
        query.prepare("SELECT nome, cpf, data_nasc, cargo, contato, email FROM tb_colaboradores WHERE id = :id");
        query.bindValue(":id", id_colaborador);                                                                           // Prepara a query para selecionar os dados do colaborador

        if (query.exec()) {
            if (query.first()) {
                ui->txtnome->setText(query.value("nome").toString());
                ui->txtCpf->setText(query.value("cpf").toString());
                ui->txtcargo->setText(query.value("cargo").toString());
                ui->txtcontato->setText(query.value("contato").toString());
                ui->txtemail->setText(query.value("email").toString());

                QDate date = QDate::fromString(query.value("data_nasc").toString(), "dd/MM/yyyy");                        // Convertendo a string da data para QDate
                ui->txtData->setDate(date);
            } else {
                QMessageBox::warning(this, "ERRO", "Não foi possível carregar os dados do colaborador.");
            }
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao carregar dados do colaborador: " + query.lastError().text());
        }
    } else {
        ui->txtData->setDate(QDate::currentDate());                                                                       // Define a data atual
    }
}

void cadastroColaboradores::on_btnCadastrarCol_clicked()
{
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString cargo = ui->txtcargo->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();

    QDate hoje = QDate::currentDate();
    int idad = hoje.year() - dataNascimento.year();                                                                       // Calculando idade
    if ((hoje.month() < dataNascimento.month()) ||
        (hoje.month() == dataNascimento.month() && hoje.day() < dataNascimento.day())) {
        idad--;
    }
    QString ida = QString::number(idad);

    QString nasc = dataNascimento.toString("dd/MM/yyyy");                                                                 // Transformando a data em string para envio pro banco de dados

    QSqlQuery query;

    if (tipoUso == "Editar") {
        query.prepare("UPDATE tb_colaboradores SET nome = :nome, idade = :idade, cpf = :cpf, cargo = :cargo, contato = :contato, "
                      "email = :email, data_nasc = :data_nasc WHERE id = :id");                                           // Prepara a query para atualizar o colaborador existente

        query.bindValue(":nome", nom);
        query.bindValue(":idade", ida);
        query.bindValue(":cpf", cpf);
        query.bindValue(":cargo", cargo);
        query.bindValue(":contato", contat);
        query.bindValue(":email", emai);
        query.bindValue(":data_nasc", nasc);
        query.bindValue(":id", getIdColaborador());

        if (query.exec()) {
            QMessageBox::information(this, "", "Edição realizada!");
            this->close();
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao editar colaborador: " + query.lastError().text());
        }
    } else {
        Colaborador colaborador(nom, cpf, contat, emai, dataNascimento, cargo);                                           // Cria um objeto Colaborador com os dados recuperados

        connect(&colaborador, &Colaborador::colaboradorCadastrado, this, &cadastroColaboradores::colaboradorCadastrado);  // Conecta o sinal colaboradorCadastrado ao slot correspondente

        if (colaborador.salvarNoBanco()) {                                                                                // Salva o objeto Colaborador no banco de dados
            QMessageBox::information(this, "", "Cadastro realizado");
            this->close();
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao cadastrar colaborador");
        }
    }
}

void cadastroColaboradores::on_btnCancelarCol_clicked()
{
    this->close();                                                                                                        // Fecha a janela
}
