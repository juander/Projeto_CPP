#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"
#include <QMessageBox>
#include <QDebug>

// DEFINIÇÃO DO CONSTRUTOR DA CLASSE CADASTROPACIENTE

cadastroPacientes::cadastroPacientes(QWidget *parent, const QString &modo, int id_paciente)
    : QDialog(parent)
    , ui(new Ui::cadastroPacientes)
{
    ui->setupUi(this);
    setIdPaciente(id_paciente);
    setModo(modo, getIdPaciente());
}

// FIM


// DEFINIÇÃO DO DESTRUTOR DA CLASSE CADASTROPACIENTE

cadastroPacientes::~cadastroPacientes()
{
    delete ui;
}

// FIM

void cadastroPacientes::setIdPaciente(int id){
    idPaciente = id;
}

int cadastroPacientes::getIdPaciente(){
    return idPaciente;
}

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
    QSqlQuery query;

    if (tipoUso == "Editar") {
        // Atualizar paciente existente

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
        // Cria um objeto Paciente com os dados recuperados                                                            // CRIA UM OBJETO PACIENTE COM OS DADOS RECUPERADOS
        Paciente paciente(nom, cpf, contat, emai, dataNascimento, conven, diagn);

        // Conecta o sinal pacienteCadastrado ao slot correspondente                                                   // CONECTA O SINAL PACIENTE CADASTRADO AO SLOT CORRESPONDENTE
        connect(&paciente, &Paciente::pacienteCadastrado, this, &cadastroPacientes::pacienteCadastrado);

        // Salva o objeto Paciente no banco de dados                                                                   // SALVA O OBJETO PACIENTE NO BANCO DE DADOS
        if (paciente.salvarNoBanco()) {
            QMessageBox::information(this, "", "Cadastro realizado");
            this->close();
        } else {
            qDebug() << "Erro ao cadastrar paciente:" << query.lastError().text();
            QMessageBox::information(this, "ERRO", "Erro ao cadastrar paciente");
        }
    }
}

// FIM


// DEFINIÇÃO DO METODO CANCELAR CADASTRO

void cadastroPacientes::on_btnCancelarPac_clicked()
{
    this->close();
}

// FIM

void cadastroPacientes::setModo(const QString &modo, int id_paciente)
{
    tipoUso = modo;

    if (modo == "Editar" && id_paciente != -1) {
        ui->btnCadastrarPac->setText("Salvar Alterações");

        QSqlQuery query;
        query.prepare("SELECT nome, cpf, data_nasc, diagnostico_pre, contato, email, convenio_plano FROM tb_pacientes WHERE id = :id");
        query.bindValue(":id", id_paciente);

        if (query.exec()) {
            qDebug() << "Query executada com sucesso";
            if (query.first()) {
                ui->txtnome->setText(query.value("nome").toString());
                ui->txtCpf->setText(query.value("cpf").toString());
                ui->txtDiagn->setText(query.value("diagnostico_pre").toString());
                ui->txtcontato->setText(query.value("contato").toString());
                ui->txtemail->setText(query.value("email").toString());
                ui->txtconvenio->setText(query.value("convenio_plano").toString());

                // Convertendo a string da data para QDate
                QDate date = QDate::fromString(query.value("data_nasc").toString(), "dd/MM/yyyy");
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
        ui->txtData->setDate(QDate::currentDate());
    }
}

