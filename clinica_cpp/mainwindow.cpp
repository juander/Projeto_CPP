#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName("banco_clinica.db");

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
    query.prepare("select * from tb_pacientes");

    if(query.exec()){
        int tb_linha = 0;

        // Limpa os dados antigos da tabela
        ui->tw_pacientes->clearContents();
        ui->tw_pacientes->setRowCount(0);  // Reseta as linhas

        ui->tw_pacientes->setColumnCount(6);
        while(query.next()){

            ui->tw_pacientes->insertRow(tb_linha);

            ui->tw_pacientes->setItem(tb_linha,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_pacientes->setItem(tb_linha,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_pacientes->setItem(tb_linha,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_pacientes->setItem(tb_linha,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tw_pacientes->setItem(tb_linha,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tw_pacientes->setItem(tb_linha,5,new QTableWidgetItem(query.value(5).toString()));

            ui->tw_pacientes->setRowHeight(tb_linha,20);

            tb_linha++;
        }
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

void MainWindow::on_btnCadastro_clicked()
{
    cadastramento = new cadastroPacientes(bancoDeDados, this);
    cadastramento->show();
}

