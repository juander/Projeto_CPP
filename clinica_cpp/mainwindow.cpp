#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName("..\\..\\banco_clinica.db");

    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao abrir o banco de dados:" << bancoDeDados.lastError().text();
    } else {
        qDebug() << "Banco de dados conectado com sucesso!";
    }

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0, 5);
    ui->frame->setGraphicsEffect(shadowEffect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAgenda_clicked()
{
    int index = ui->paginas->indexOf(ui->Agenda);
    ui->paginas->setCurrentIndex(index);
}

void MainWindow::on_btnAtendimento_clicked()
{
    int index = ui->paginas->indexOf(ui->Atendimento);
    ui->paginas->setCurrentIndex(index);
}

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

void MainWindow::on_btnProfissionais_clicked()
{
    int index = ui->paginas->indexOf(ui->Profissionais);
    ui->paginas->setCurrentIndex(index);
}

void MainWindow::on_btnRelatorios_clicked()
{
    int index = ui->paginas->indexOf(ui->Relatorios);
    ui->paginas->setCurrentIndex(index);
}

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
        for(int i = 0; i <= 7; i++){
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
        for(int i = 1; i <= 7; i++){
            ui->tw_pacientes->setItem(linha,i,new QTableWidgetItem(query.value(i).toString()));
        }
    }else{
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar paciente na tabela");
    }
}

void MainWindow::on_btnPesquisarPac_clicked()
{
    QString nome = ui->lineEdit->text(); // Pegando o texto do QLineEdit

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");
    query.bindValue(":nome", nome + "%");

    if(query.exec()){
        setTabelaPacientes(query);
    }else{
        QMessageBox::warning(this, "ERRO", "Não foi possível acessar os pacientes no banco de dados");
    }
}

void MainWindow::setTabelaPacientes(QSqlQuery &query)
{
    int tb_linha = 0;

    // Limpa os dados antigos da tabela
    ui->tw_pacientes->clearContents();
    ui->tw_pacientes->setRowCount(0);  // Reseta as linhas

    ui->tw_pacientes->setColumnCount(8);
    while(query.next()){

        ui->tw_pacientes->insertRow(tb_linha);

        for(int i = 0; i <= 7; i++){
            ui->tw_pacientes->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));
        }
        ui->tw_pacientes->setRowHeight(tb_linha,20);

        tb_linha++;
    }

    // Setando a largura das colunas da tabela
    ui->tw_pacientes->setColumnWidth(0, 80);
    ui->tw_pacientes->setColumnWidth(1, 280);
    ui->tw_pacientes->setColumnWidth(2, 40);
    ui->tw_pacientes->setColumnWidth(3, 135);
    ui->tw_pacientes->setColumnWidth(4, 124);
    ui->tw_pacientes->setColumnWidth(5, 180);
    ui->tw_pacientes->setColumnWidth(6, 135);
    ui->tw_pacientes->setColumnWidth(7, 115);

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
    ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
    ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_pacientes->verticalHeader()->setVisible(false);
    ui->tw_pacientes->setStyleSheet("QTableWidget::item:selected {background-color: blue}");
}

