#include "cadastrosessao.h"
#include "ui_cadastrosessao.h"

cadastroSessao::cadastroSessao(MainWindow *mainWindow, const QString &modo, int idSessao, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroSessao)
{
    ui->setupUi(this);

    setConexaoJanelaPrincipal(mainWindow);                                                               // Define a conexão com a janela principal
    setIdSessao(idSessao);                                                                               // Define o ID da sessão
    setTipoUso(modo);                                                                                    // Define o tipo de uso

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes");                                                         // Prepara a query para selecionar todos os pacientes

    if (query.exec()) {
        setTabelaPacSes(query);                                                                          // Define a tabela de pacientes
    } else {
        qDebug() << "Erro ao carregar a tabela de pacientes na janela de cadastro de sessões";
    }

    setModo(getTipoUso());                                                                               // Define o modo (Cadastrar ou Editar)
}

cadastroSessao::~cadastroSessao()
{
    delete ui;                                                                                           // Destrói a interface do usuário
}

void cadastroSessao::setIdSessao(int id)
{
    m_idSessao = id;                                                                                     // Define o ID da sessão
}

int cadastroSessao::getIdSessao() const
{
    return m_idSessao;                                                                                   // Retorna o ID da sessão
}

void cadastroSessao::setTipoUso(const QString &modo)
{
    tipoUso = modo;                                                                                      // Define o tipo de uso (Cadastrar ou Editar)
}

QString cadastroSessao::getTipoUso() const
{
    return tipoUso;                                                                                      // Retorna o tipo de uso
}

void cadastroSessao::setConexaoJanelaPrincipal(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;                                                                           // Define a conexão com a janela principal
}

MainWindow* cadastroSessao::getMainWindow() const
{
    return m_mainWindow;                                                                                 // Retorna a conexão com a janela principal
}

void cadastroSessao::setModo(const QString &modo)
{
    setTipoUso(modo);                                                                                    // Define o tipo de uso

    if (modo == "Editar" && getIdSessao() != -1) {
        ui->btnCadastrarSes->setText("Salvar Alterações");                                               // Altera o texto do botão para "Salvar Alterações"

        QSqlQuery query;
        query.prepare("SELECT profissional, paciente, especialidade, data, hora FROM tb_agendamentos WHERE id = :id");
        query.bindValue(":id", getIdSessao());                                                           // Prepara a query para selecionar os dados da sessão

        if (query.exec() && query.first()) {
            ui->txtPacienteSelecionado->setText(query.value("paciente").toString());
            ui->comboBoxEspecialidades->setCurrentText(query.value("especialidade").toString());

            QDate data = QDate::fromString(query.value("data").toString(), "dd/MM/yyyy");                // Convertendo strings de data e hora para os formatos corretos
            ui->dataAgenda->setDate(data);

            QTime hora = QTime::fromString(query.value("hora").toString(), "hh:mm");
            ui->horaAgenda->setTime(hora);
        } else {
            QMessageBox::warning(this, " ", "Não foi possível carregar os dados da sessão.");
        }
    } else {
        ui->dataAgenda->setDate(QDate::currentDate());                                                   // Define a data atual
    }
}

void cadastroSessao::on_tw_paciente_ses_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow >= 0) {                                                                               // Verifica se há uma linha selecionada
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
        query.prepare("UPDATE tb_agendamentos SET data = :data, hora = :hora, paciente = :paciente, especialidade = :especialidade "
                      "WHERE id = :idSessao");                                                           // Prepara a query para atualizar a sessão existente

        query.bindValue(":data", data);
        query.bindValue(":hora", hora);
        query.bindValue(":paciente", paciente);
        query.bindValue(":especialidade", especialidade);
        query.bindValue(":idSessao", getIdSessao());

        if (query.exec()) {
            QMessageBox::information(this, "", "Sessão atualizada com sucesso!");
            emit sessaoEditada();                                                                         // Emite o sinal para atualizar a tabela
            this->close();
        } else {
            qDebug() << "Erro ao atualizar a sessão.";
        }
    } else {
        query.prepare("INSERT INTO tb_agendamentos (profissional, paciente, especialidade, data, hora, status_sessao, id_profissional) "
                      "VALUES (:profissional, :paciente, :especialidade, :data, :hora, :status_sessao, :id_profissional)"); // Prepara a query para inserir uma nova sessão

        query.bindValue(":profissional", getMainWindow()->getNomeUsuario());
        query.bindValue(":paciente", paciente);
        query.bindValue(":especialidade", especialidade);
        query.bindValue(":data", data);
        query.bindValue(":hora", hora);
        query.bindValue(":status_sessao", "Aguardando");
        query.bindValue(":id_profissional", getMainWindow()->getIdUsuario());

        if (query.exec()) {
            emit sessaoCadastrada();                                                                     // Emite o sinal para atualizar a tabela
            QMessageBox::information(this, "", "Nova sessão cadastrada com sucesso!");
            this->close();
        } else {
            QMessageBox::warning(this, " ", "Erro ao salvar a sessão.");
        }
    }
}

void cadastroSessao::on_btnCancelarSes_clicked()
{
    this->close();                                                                                       // Fecha a janela
}

void cadastroSessao::redimensionarTable(QTableWidget* table)
{
    table->resizeColumnsToContents();                                                                    // Redimensiona as colunas para ajustar ao conteúdo
    for (int i = 0; i < table->columnCount(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);                        // Define o modo de redimensionamento das colunas
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                               // Define o modo de redimensionamento das colunas

    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->item(row, col);
            if (item) {
                item->setToolTip(item->text());                                                          // Define o tooltip com o texto completo
                item->setTextAlignment(Qt::AlignCenter);                                                 // Alinha o texto ao centro
            }
        }
    }
}

void cadastroSessao::setTabelaPacSes(QSqlQuery &query)
{
    int tb_linha = 0;
    ui->tw_paciente_ses->clearContents();                                                                // Limpa o conteúdo da tabela
    ui->tw_paciente_ses->setRowCount(0);                                                                 // Define o número de linhas como 0

    ui->tw_paciente_ses->setColumnCount(9);                                                              // Define o número de colunas como 9
    while (query.next()) {
        ui->tw_paciente_ses->insertRow(tb_linha);                                                        // Insere uma nova linha na tabela

        for (int i = 0; i <= 8; i++) {
            ui->tw_paciente_ses->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));  // Define o item da tabela com o valor da query
        }
        ui->tw_paciente_ses->setRowHeight(tb_linha, 30);                                                 // Define a altura da linha
        tb_linha++;
    }

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
    ui->tw_paciente_ses->setHorizontalHeaderLabels(cabecalho);                                           // Define os rótulos das colunas
    ui->tw_paciente_ses->setEditTriggers(QAbstractItemView::NoEditTriggers);                             // Define que os itens não podem ser editados
    ui->tw_paciente_ses->setSelectionBehavior(QAbstractItemView::SelectRows);                            // Define o comportamento de seleção como seleção de linhas
    ui->tw_paciente_ses->verticalHeader()->setVisible(false);                                            // Oculta o cabeçalho vertical
    ui->tw_paciente_ses->setStyleSheet("QTableWidget::item:selected {background-color: blue}");          // Define o estilo da tabela

    redimensionarTable(ui->tw_paciente_ses);                                                             // Redimensiona a tabela

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
    query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");                                   // Prepara a query para pesquisar pacientes pelo nome
    query.bindValue(":nome", nome + "%");

    if (query.exec()) {
        setTabelaPacSes(query);                                                                          // Define a tabela de pacientes
    } else {
        QMessageBox::warning(this, " ", "Não foi possível acessar os pacientes no banco de dados");
    }
}
