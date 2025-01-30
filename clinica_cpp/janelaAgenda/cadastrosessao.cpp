#include "cadastrosessao.h"
#include "ui_cadastrosessao.h"

cadastroSessao::cadastroSessao(MainWindow *mainWindow, const QString &modo, int idSessao, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroSessao)
{
    ui->setupUi(this);

    setConexaoJanelaPrincipal(mainWindow);
    setIdSessao(idSessao);
    setTipoUso(modo);

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes");

    if (query.exec()) {
        setTabelaPacSes(query);
    } else {
        qDebug() << "Erro ao carregar a tabela de pacientes na janela de cadastro de sessões";
    }

    setModo(getTipoUso());
}

cadastroSessao::~cadastroSessao()
{
    delete ui;
}

// Métodos get e set para m_idSessao
void cadastroSessao::setIdSessao(int id)
{
    m_idSessao = id;
}

int cadastroSessao::getIdSessao() const
{
    return m_idSessao;
}

// Métodos get e set para tipoUso
void cadastroSessao::setTipoUso(const QString &modo)
{
    tipoUso = modo;
}

QString cadastroSessao::getTipoUso() const
{
    return tipoUso;
}

// Métodos get e set para m_mainWindow
void cadastroSessao::setConexaoJanelaPrincipal(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

MainWindow* cadastroSessao::getMainWindow() const
{
    return m_mainWindow;
}

void cadastroSessao::setModo(const QString &modo)
{
    setTipoUso(modo);

    if (modo == "Editar" && getIdSessao() != -1) {
        ui->btnCadastrarSes->setText("Salvar Alterações");

        QSqlQuery query;
        query.prepare("SELECT profissional, paciente, especialidade, data, hora FROM tb_agendamentos WHERE id = :id");
        query.bindValue(":id", getIdSessao());

        if (query.exec() && query.first()) {
            ui->txtPacienteSelecionado->setText(query.value("paciente").toString());
            ui->comboBoxEspecialidades->setCurrentText(query.value("especialidade").toString());

            // Convertendo strings de data e hora para os formatos corretos
            QDate data = QDate::fromString(query.value("data").toString(), "dd/MM/yyyy");
            ui->dataAgenda->setDate(data);

            QTime hora = QTime::fromString(query.value("hora").toString(), "hh:mm");
            ui->horaAgenda->setTime(hora);
        } else {
            QMessageBox::warning(this, " ", "Não foi possível carregar os dados da sessão.");
        }
    } else {
        ui->dataAgenda->setDate(QDate::currentDate());
    }
}

void cadastroSessao::on_tw_paciente_ses_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow >= 0) {  // Verifica se há uma linha selecionada
        QString valor = ui->tw_paciente_ses->item(currentRow, 1)->text();
        ui->txtPacienteSelecionado->setText(valor);
    }
}

void cadastroSessao::on_btnCadastrarSes_clicked()
{
    QString data = ui->dataAgenda->date().toString("dd/MM/yyyy");
    QString hora = ui->horaAgenda->time().toString("hh:mm");
    QString paciente = ui->txtPacienteSelecionado->text();
    QString especialidade = ui->comboBoxEspecialidades->currentText();

    if (paciente.isEmpty() || especialidade.isEmpty() || data.isEmpty() || hora.isEmpty()) {
        QMessageBox::warning(this, " ", "Todos os campos devem ser preenchidos.");
        return;
    }

    if (paciente == "") {
        QMessageBox::information(this, " ", "Nenhuma paciente foi selecionado");
        return;
    }

    QSqlQuery query;

    if (getTipoUso() == "Editar") {
        // Atualizar sessão existente
        query.prepare("UPDATE tb_agendamentos SET data = :data, hora = :hora, paciente = :paciente, especialidade = :especialidade "
                      "WHERE id = :idSessao");

        query.bindValue(":data", data);
        query.bindValue(":hora", hora);
        query.bindValue(":paciente", paciente);
        query.bindValue(":especialidade", especialidade);
        query.bindValue(":idSessao", getIdSessao());

        if (query.exec()) {
            QMessageBox::information(this, "", "Sessão atualizada com sucesso!");
            emit sessaoEditada();
            this->close();
        } else {
            qDebug() << "Erro ao atualizar a sessão.";
        }
    } else {
        // Inserir nova sessão
        query.prepare("INSERT INTO tb_agendamentos (profissional, paciente, especialidade, data, hora, status_sessao, id_profissional) "
                      "VALUES (:profissional, :paciente, :especialidade, :data, :hora, :status_sessao, :id_profissional)");

        query.bindValue(":profissional", getMainWindow()->getNomeUsuario());
        query.bindValue(":paciente", paciente);
        query.bindValue(":especialidade", especialidade);
        query.bindValue(":data", data);
        query.bindValue(":hora", hora);
        query.bindValue(":status_sessao", "Aguardando");
        query.bindValue(":id_profissional", getMainWindow()->getIdUsuario());

        if (query.exec()) {
            emit sessaoCadastrada();  // Emite o sinal para atualizar a tabela
            QMessageBox::information(this, "", "Nova sessão cadastrada com sucesso!");
            this->close();
        } else {
            QMessageBox::warning(this, " ", "Erro ao salvar a sessão.");
        }
    }
}

void cadastroSessao::on_btnCancelarSes_clicked()
{
    this->close();
}

void cadastroSessao::redimensionarTable(QTableWidget* table)
{
    table->resizeColumnsToContents();
    for (int i = 0; i < table->columnCount(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->item(row, col);
            if (item) {
                item->setToolTip(item->text());
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void cadastroSessao::setTabelaPacSes(QSqlQuery &query)
{
    int tb_linha = 0;
    ui->tw_paciente_ses->clearContents();
    ui->tw_paciente_ses->setRowCount(0);

    ui->tw_paciente_ses->setColumnCount(9);
    while (query.next()) {
        ui->tw_paciente_ses->insertRow(tb_linha);

        for (int i = 0; i <= 8; i++) {
            ui->tw_paciente_ses->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));
        }
        ui->tw_paciente_ses->setRowHeight(tb_linha, 30);
        tb_linha++;
    }

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
    ui->tw_paciente_ses->setHorizontalHeaderLabels(cabecalho);
    ui->tw_paciente_ses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_paciente_ses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_paciente_ses->verticalHeader()->setVisible(false);
    ui->tw_paciente_ses->setStyleSheet("QTableWidget::item:selected {background-color: blue}");

    redimensionarTable(ui->tw_paciente_ses);

    ui->tw_paciente_ses->setStyleSheet(
        "QTableWidget {"
        "    border: 3px solid #dcdcdc;"
        "    border-radius: 10px;"
        "    background-color: #ffffff;"
        "    gridline-color: #dcdcdc;"
        "}"
        "QHeaderView::section {"
        "    background-color: #f0f0f0;"
        "    border: 1px solid #dcdcdc;"
        "    padding: 5px;"
        "    border-radius: 5px;"
        "}"
        "QTableWidget::item {"
        "    border-bottom: 1px solid #dcdcdc;"
        "    padding: 5px;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #a0c4ff;"
        "    color: #000000;"
        "}"
        );
}

void cadastroSessao::on_pesquisarPacAg_textChanged(const QString &arg1)
{
    QString nome = ui->pesquisarPacAg->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");
    query.bindValue(":nome", nome + "%");

    if (query.exec()) {
        setTabelaPacSes(query);
    } else {
        QMessageBox::warning(this, " ", "Não foi possível acessar os pacientes no banco de dados");
    }
}
