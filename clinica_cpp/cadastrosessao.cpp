#include "cadastrosessao.h"
#include "ui_cadastrosessao.h"

cadastroSessao::cadastroSessao(MainWindow *mainWindow, const QString &modo, int idSessao, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroSessao)
    , m_mainWindow(mainWindow)
    , tipoUso(modo)
    , m_idSessao(idSessao)

{
    ui->setupUi(this);

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes");

    if (query.exec()){
        setTabelaPacSes(query);
    } else {
        qDebug() << "Erro ao carregar a tabela de pacientes na janela de cadastro de sessões";
    }

    setModo(tipoUso);
}

cadastroSessao::~cadastroSessao()
{
    delete ui;
}


void cadastroSessao::setModo(const QString &modo)
{
    tipoUso = modo;

    if (modo == "Editar" && m_idSessao != -1) {
        ui->btnCadastrarSes->setText("Salvar Alterações");
        ui->tituloSessao->setText("Editar sessão");
        this->setWindowTitle("Editar Sessão");

        QSqlQuery query;
        query.prepare("SELECT profissional, paciente, especialidade, data, hora FROM tb_agendamentos WHERE id = :id");
        query.bindValue(":id", m_idSessao);

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

        this->setWindowTitle("Nova Sessão");
    }
}


void cadastroSessao::on_tw_paciente_ses_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow >= 0) {  // Verifica se há uma linha selecionada
        QString valor = ui->tw_paciente_ses->item(currentRow, 1)->text();
        ui->txtPacienteSelecionado->setText(valor);
    }
}

// DEFINIÇÃO DO METODO CADASTRAR SESSÃO

void cadastroSessao::on_btnCadastrarSes_clicked()
{
    QString data = ui->dataAgenda->date().toString("dd/MM/yyyy");

    QString hora = ui->horaAgenda->time().toString("hh:mm");                                                        // OBTÉM OS DADOS DOS CAMPOS DA SESSÃO

    QString paciente = ui->txtPacienteSelecionado->text();

    QString especialidade = ui->comboBoxEspecialidades->currentText(); // Opção do comboBox

    if (paciente.isEmpty() || especialidade.isEmpty() || data.isEmpty() || hora.isEmpty()) {
        QMessageBox::warning(this, " ", "Todos os campos devem ser preenchidos antes de salvar.");
        return;
    }

    if (paciente == "") {                                                                                               // SÓ SE TIVER ALGUMA LINHA SELECIONADA POIS CURRENTROW RETORNA -1 CASO NÃO
        QMessageBox::information(this, " ", "Nenhuma paciente foi selecionado");
        return;
    }

    QSqlQuery query;

    if (tipoUso == "Editar") {

        // Atualizar sessão existente
        query.prepare("UPDATE tb_agendamentos SET data = :data, hora = :hora, paciente = :paciente, especialidade = :especialidade "
                      "WHERE id = :idSessao");

        query.bindValue(":data", data);
        query.bindValue(":hora", hora);
        query.bindValue(":paciente", paciente);
        query.bindValue(":especialidade", especialidade);
        query.bindValue(":idSessao", m_idSessao);

        if (query.exec()) {
            QMessageBox::information(this, "", "Sessão atualizada com sucesso!");
            this->close();
        } else {
            qDebug() << "Erro ao atualizar a sessão." ;
        }

    } else {

        // Inserir nova sessão

        query.prepare("INSERT INTO tb_agendamentos (profissional, paciente, especialidade, data, hora, status_sessao, id_profissional) "
                      "VALUES (:profissional, :paciente, :especialidade, :data, :hora, :status_sessao, :id_profissional)");

        query.bindValue(":profissional", m_mainWindow->getNomeUsuario());
        query.bindValue(":paciente", paciente);
        query.bindValue(":especialidade", especialidade);
        query.bindValue(":data", data);
        query.bindValue(":hora", hora);
        query.bindValue(":status_sessao", "Aguardando");
        query.bindValue(":id_profissional", m_mainWindow->getIdUsuario());

        if (query.exec()) {

            int idSessao = query.lastInsertId().toInt();
            emit sessaoCadastrada(idSessao);  // Emite o sinal para atualizar a tabela

            QMessageBox::information(this, "", "Nova sessão cadastrada com sucesso!");
            this->close();

        } else {
            QMessageBox::warning(this, " ", "Erro ao salvar a sessão.");
        }
    }
}

// FIM


// DEFINIÇÃO DO METODO CANCELAR CADASTRO

void cadastroSessao::on_btnCancelarSes_clicked()
{
    this->close();
}

// FIM

void cadastroSessao::redimensionarTable(QTableWidget* table)
{

    table->resizeColumnsToContents();  // Ajusta as colunas ao conteúdo

    // Agora, fazemos as colunas se expandirem para preencher a largura total da tabela
    for (int i = 0; i < table->columnCount(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Após redimensionar as colunas, fazemos o ajuste de layout
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Adicionando Tooltips para mostrar o conteúdo completo ao passar o mouse sobre a célula
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->item(row, col);
            if (item) {
                // Define o conteúdo completo da célula como o Tooltip
                item->setToolTip(item->text());
                // Alinha os itens das tabelas no centro das colunas
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void cadastroSessao::setTabelaPacSes(QSqlQuery &query)
{
    int tb_linha = 0;

    // Limpa os dados antigos da tabela
    ui->tw_paciente_ses->clearContents();
    ui->tw_paciente_ses->setRowCount(0);  // Reseta as linhas

    ui->tw_paciente_ses->setColumnCount(9);                                                                        // SETA A TABLE EM 9 COLUNAS
    while(query.next()){

        ui->tw_paciente_ses->insertRow(tb_linha);

        for(int i = 0; i <= 8; i++){
            ui->tw_paciente_ses->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));              // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
        }
        ui->tw_paciente_ses->setRowHeight(tb_linha,30);

        tb_linha++;
    }

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
    ui->tw_paciente_ses->setHorizontalHeaderLabels(cabecalho);
    ui->tw_paciente_ses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_paciente_ses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_paciente_ses->verticalHeader()->setVisible(false);
    ui->tw_paciente_ses->setStyleSheet("QTableWidget::item:selected {background-color: blue}");

    redimensionarTable(ui->tw_paciente_ses);                                                                       // REDIMENSIONANDO A TABELA
}

void cadastroSessao::on_pesquisarPacAg_textChanged(const QString &arg1)
{
    QString nome = ui->pesquisarPacAg->text(); // Pegando o texto do linePesquisaPac                               // MÉTODO SLOT DO QT PARA RECONHCER O QUE ESTÁ SENDO DIGITADO NA LINHA EM TEMPO REAL

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");                                              // FAZENDO A QUERY DE SELECT PELO NOME
    query.bindValue(":nome", nome + "%");

    if(query.exec()){
        setTabelaPacSes(query);                                                                                  // SETANDO A TABLE EM TEMPO REAL
    }else{
        QMessageBox::warning(this, " ", "Não foi possível acessar os pacientes no banco de dados");
    }
}

