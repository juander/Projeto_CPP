#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"
#include <QMessageBox>
#include <QDebug>

cadastroPacientes::cadastroPacientes(QWidget *parent, const QString &modo, int id_paciente)
    : QDialog(parent)
    , ui(new Ui::cadastroPacientes)
{
    ui->setupUi(this);
    setIdPaciente(id_paciente);                                                                                             // Define o ID do paciente
    setModo(modo, getIdPaciente());                                                                                         // Define o modo (Cadastrar ou Editar)
}

cadastroPacientes::~cadastroPacientes()
{
    delete ui;                                                                                                              // Destrói a interface do usuário
}

void cadastroPacientes::setIdPaciente(int id){
    idPaciente = id;                                                                                                        // Define o ID do paciente
}

int cadastroPacientes::getIdPaciente(){
    return idPaciente;                                                                                                      // Retorna o ID do paciente
}

void cadastroPacientes::on_btnCadastrarPac_clicked()
{
    QString nom = ui->txtnome->text();
    QString cpf = ui->txtCpf->text();
    QDate dataNascimento = ui->txtData->date();
    QString diagn = ui->txtDiagn->text();
    QString contat = ui->txtcontato->text();
    QString emai = ui->txtemail->text();
    QString conven = ui->txtconvenio->text();

    QDate hoje = QDate::currentDate();
    int idad = hoje.year() - dataNascimento.year();                                                                         // Calculando idade

    if ((hoje.month() < dataNascimento.month()) ||
        (hoje.month() == dataNascimento.month() && hoje.day() < dataNascimento.day())) {
        idad--;
    }

    QString ida = QString::number(idad);

    QString nasc = dataNascimento.toString("dd/MM/yyyy");                                                                   // Transformando a data em string para envio pro banco de dados
    QSqlQuery query;

    if (tipoUso == "Editar") {
        query.prepare("UPDATE tb_pacientes SET nome = :nome, idade = :idade, cpf = :cpf, diagnostico_pre = :diagnostico_pre, contato = :contato, "
                      "email = :email, convenio_plano = :convenio_plano, data_nasc = :data_nasc WHERE id = :id");

        query.bindValue(":nome", nom);
        query.bindValue(":idade", ida);
        query.bindValue(":cpf", cpf);
        query.bindValue(":diagnostico_pre", diagn);
        query.bindValue(":contato", contat);
        query.bindValue(":email", emai);
        query.bindValue(":convenio_plano", conven);
        query.bindValue(":data_nasc", nasc);
        query.bindValue(":id", getIdPaciente());

        if (query.exec()) {
            qDebug() << getIdPaciente();
            QMessageBox::information(this, "", "Edição realizada!");
            this->close();
        } else {
            qDebug() << "Erro ao editar paciente:" << query.lastError().text();
            QMessageBox::warning(this, "ERRO", "Erro ao editar paciente");
        }
    } else {
        Paciente paciente(nom, cpf, contat, emai, dataNascimento, conven, diagn);                                           // Cria um objeto Paciente com os dados recuperados

        connect(&paciente, &Paciente::pacienteCadastrado, this, &cadastroPacientes::pacienteCadastrado);                    // Conecta o sinal pacienteCadastrado ao slot correspondente

        if (paciente.salvarNoBanco()) {                                                                                     // Salva o objeto Paciente no banco de dados
            QMessageBox::information(this, "", "Cadastro realizado");
            this->close();
        } else {
            qDebug() << "Erro ao cadastrar paciente:" << query.lastError().text();
            QMessageBox::information(this, "ERRO", "Erro ao cadastrar paciente");
        }
    }
}

void cadastroPacientes::on_btnCancelarPac_clicked()
{
    this->close();                                                                                                          // Fecha a janela
}

void cadastroPacientes::setModo(const QString &modo, int id_paciente)
{
    tipoUso = modo;                                                                                                         // Define o tipo de uso

    if (modo == "Editar" && id_paciente != -1) {
        ui->btnCadastrarPac->setText("Salvar Alterações");                                                                  // Altera o texto do botão para "Salvar Alterações"

        QSqlQuery query;
        query.prepare("SELECT nome, cpf, data_nasc, diagnostico_pre, contato, email, convenio_plano FROM tb_pacientes WHERE id = :id");
        query.bindValue(":id", id_paciente);                                                                                // Prepara a query para selecionar os dados do paciente

        if (query.exec()) {
            qDebug() << "Query executada com sucesso";
            if (query.first()) {
                ui->txtnome->setText(query.value("nome").toString());
                ui->txtCpf->setText(query.value("cpf").toString());
                ui->txtDiagn->setText(query.value("diagnostico_pre").toString());
                ui->txtcontato->setText(query.value("contato").toString());
                ui->txtemail->setText(query.value("email").toString());
                ui->txtconvenio->setText(query.value("convenio_plano").toString());

                QDate date = QDate::fromString(query.value("data_nasc").toString(), "dd/MM/yyyy");                          // Convertendo a string da data para QDate
                ui->txtData->setDate(date);
            } else {
                qDebug() << "Nenhum registro encontrado";
                QMessageBox::warning(this, "ERRO", "Não foi possível carregar os dados do paciente.");
            }
        } else {
            qDebug() << "Erro ao executar query:" << query.lastError().text();
            QMessageBox::warning(this, "ERRO", "Não foi possível carregar os dados do paciente.");
        }
    } else {
        ui->txtData->setDate(QDate::currentDate());                                                                         // Define a data atual
    }
}

