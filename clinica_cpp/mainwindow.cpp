#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuração do banco de dados SQLite
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName("..\\..\\banco_clinica.db");

    // Verificação da conexão com o banco de dados
    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao abrir o banco de dados:" << bancoDeDados.lastError().text();
    } else {
        qDebug() << "Banco de dados conectado com sucesso!";
    }

    // Adicionando efeito de sombra ao frame superior
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0, 5);
    ui->frame->setGraphicsEffect(shadowEffect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Método para trocar para a aba "Agenda"
void MainWindow::on_btnAgenda_clicked()
{
    int index = ui->paginas->indexOf(ui->Agenda);
    ui->paginas->setCurrentIndex(index);
}

// Método para trocar para a aba "Atendimento"
void MainWindow::on_btnAtendimento_clicked()
{
    int index = ui->paginas->indexOf(ui->Atendimento);
    ui->paginas->setCurrentIndex(index);
}

// Método para trocar para a aba "Pacientes" e carregar os dados dos pacientes
void MainWindow::on_btnPacientes_clicked()
{
    int index = ui->paginas->indexOf(ui->Pacientes);
    ui->paginas->setCurrentIndex(index);

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes");

    if(query.exec()){
        setTabelaPacientes(query);

    }else{
        QMessageBox::warning(this, "ERRO", "Não foi possível acessar os pacientes no banco de dados");
    }
}

// Método para trocar para a aba "Profissionais"
void MainWindow::on_btnProfissionais_clicked()
{
    int index = ui->paginas->indexOf(ui->Colaboradores);
    ui->paginas->setCurrentIndex(index);

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_colaboradores");

    if(query.exec()){
        setTabelaColaboradores(query);

    }else{
        QMessageBox::warning(this, "ERRO", "Não foi possível acessar os colaboradores no banco de dados");
    }
}

// Método para trocar para a aba "Relatórios"
void MainWindow::on_btnRelatorios_clicked()
{
    int index = ui->paginas->indexOf(ui->Relatorios);
    ui->paginas->setCurrentIndex(index);
}

// Método para trocar para a aba "Fornecedores"
void MainWindow::on_btnFornecedores_clicked()
{
    int index = ui->paginas->indexOf(ui->Fornecedores);
    ui->paginas->setCurrentIndex(index);
}

// Novo método para carregar o paciente pelo ID
void MainWindow::adicionarPacienteNaTabela(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE id = :id");
    query.bindValue(":id", id);

    if(query.exec() && query.first()){
        int linha = ui->tw_pacientes->rowCount();
        ui->tw_pacientes->insertRow(linha);
        for(int i = 0; i <= 8; i++){
            ui->tw_pacientes->setItem(linha, i, new QTableWidgetItem(query.value(i).toString()));
        }
    } else {
        QMessageBox::warning(this, "ERRO", "Erro ao carregar o novo paciente.");
    }
}

// Cadastro de novo paciente usando o novo método para atualizar a table
void MainWindow::on_btnCadastro_clicked()
{
    cadastroPacientes cadastramento(this);
    connect(&cadastramento, &cadastroPacientes::pacienteCadastrado, this, &MainWindow::adicionarPacienteNaTabela);
    cadastramento.exec();
}

// Método para apagar um paciente selecionado
void MainWindow::on_btnApagarPac_clicked()
{
    // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
    if (ui->tw_pacientes->currentRow() == -1) {
        QMessageBox::warning(nullptr, "Aviso", "Nenhuma paciente foi selecionado.");
        return;
    }
    // Verificando qual é a linha selecionada e descobrindo o id dela
    int linha = ui->tw_pacientes->currentRow();
    QString id = ui->tw_pacientes->item(linha, 0)->text();

    // Query para excluir
    QSqlQuery query;
    query.prepare("DELETE FROM tb_pacientes WHERE id="+id);

    if(query.exec()){
        // Removendo a linha do Table
        ui->tw_pacientes->removeRow(linha);
        QMessageBox::information(this,"","Excluído");
    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao excluir registro");
    }
}

// Método para editar um paciente selecionado
void MainWindow::on_btnEditarPac_clicked()
{
    // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
    if (ui->tw_pacientes->currentRow() == -1) {
        QMessageBox::warning(nullptr, "Aviso", "Nenhuma paciente foi selecionado.");
        return;
    }
    int linha = ui->tw_pacientes->currentRow();
    int id = ui->tw_pacientes->item(linha, 0)->text().toInt();

    edicaopaciente editarPaciente(this, id);
    editarPaciente.exec();

    // Carregar paciente na Table novamente
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE id="+QString::number(id));

    if(query.exec()){
        query.first();
        for(int i = 1; i <= 8; i++){
            ui->tw_pacientes->setItem(linha,i,new QTableWidgetItem(query.value(i).toString()));
        }
    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar paciente na tabela");
    }
}

// Método para configurar a tabela de pacientes
void MainWindow::setTabelaPacientes(QSqlQuery &query)
{
    int tb_linha = 0;

    // Limpa os dados antigos da tabela
    ui->tw_pacientes->clearContents();
    ui->tw_pacientes->setRowCount(0);  // Reseta as linhas

    ui->tw_pacientes->setColumnCount(9);
    while(query.next()){

        ui->tw_pacientes->insertRow(tb_linha);

        for(int i = 0; i <= 8; i++){
            ui->tw_pacientes->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));
        }
        ui->tw_pacientes->setRowHeight(tb_linha,20);

        tb_linha++;
    }

    // Setando a largura das colunas da tabela
    ui->tw_pacientes->setColumnWidth(0, 80);  // ID
    ui->tw_pacientes->setColumnWidth(1, 280); // Nome
    ui->tw_pacientes->setColumnWidth(2, 40);  // Idade
    ui->tw_pacientes->setColumnWidth(3, 135); // CPF
    ui->tw_pacientes->setColumnWidth(4, 150); // Diagnóstico
    ui->tw_pacientes->setColumnWidth(5, 124); // NºCelular
    ui->tw_pacientes->setColumnWidth(6, 180); // E-mail
    ui->tw_pacientes->setColumnWidth(7, 135); // Convênio/Plano
    ui->tw_pacientes->setColumnWidth(8, 70); // Nascimento

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
    ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
    ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_pacientes->verticalHeader()->setVisible(false);
    ui->tw_pacientes->setStyleSheet("QTableWidget::item:selected {background-color: blue}");
}

// Método para configurar a tabela de colaboradores
void MainWindow::setTabelaColaboradores(QSqlQuery &query)
{
    int tb_linha = 0;

    // Limpa os dados antigos da tabela
    ui->tw_colaboradores->clearContents();
    ui->tw_colaboradores->setRowCount(0);  // Reseta as linhas

    ui->tw_colaboradores->setColumnCount(8);
    while(query.next()){

        ui->tw_colaboradores->insertRow(tb_linha);

        for(int i = 0; i <= 7; i++){
            ui->tw_colaboradores->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));
        }
        ui->tw_colaboradores->setRowHeight(tb_linha,20);

        tb_linha++;
    }

    // Setando a largura das colunas da tabela
    ui->tw_colaboradores->setColumnWidth(0, 80);  // ID
    ui->tw_colaboradores->setColumnWidth(1, 280); // Nome
    ui->tw_colaboradores->setColumnWidth(2, 40);  // Idade
    ui->tw_colaboradores->setColumnWidth(3, 135); // CPF
    ui->tw_colaboradores->setColumnWidth(3, 135); // Cargo
    ui->tw_colaboradores->setColumnWidth(5, 124); // NºCelular
    ui->tw_colaboradores->setColumnWidth(6, 180); // E-mail
    ui->tw_colaboradores->setColumnWidth(7, 70); // Nascimento

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Cargo", "NºCelular", "E-mail", "Nascimento"};
    ui->tw_colaboradores->setHorizontalHeaderLabels(cabecalho);
    ui->tw_colaboradores->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_colaboradores->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_colaboradores->verticalHeader()->setVisible(false);
    ui->tw_colaboradores->setStyleSheet("QTableWidget::item:selected {background-color: blue}");
}


// Método para pesquisar pacientes pelo nome
void MainWindow::on_linePesquisa_textChanged(const QString &arg1)
{
    QString nome = ui->linePesquisa->text(); // Pegando o texto do linePesquisa

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");
    query.bindValue(":nome", nome + "%");

    if(query.exec()){
        setTabelaPacientes(query);
    }else{
        QMessageBox::warning(this, "ERRO", "Não foi possível acessar os pacientes no banco de dados");
    }
}


// Novo método para carregar o colaborador pelo ID
void MainWindow::adicionarColaboradorNaTabela(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_colaboradores WHERE id = :id");
    query.bindValue(":id", id);

    if(query.exec() && query.first()){
        int linha = ui->tw_colaboradores->rowCount();
        ui->tw_colaboradores->insertRow(linha);
        for(int i = 0; i <= 8; i++){
            ui->tw_colaboradores->setItem(linha, i, new QTableWidgetItem(query.value(i).toString()));
        }
    } else {
        QMessageBox::warning(this, "ERRO", "Erro ao carregar o novo colaborador.");
    }
}

void MainWindow::on_btnCadastro_2_clicked()
{
    cadastroColaboradores cadastramento(this);
    connect(&cadastramento, &cadastroColaboradores::colaboradorCadastrado, this, &MainWindow::adicionarColaboradorNaTabela);
    cadastramento.exec();
}

