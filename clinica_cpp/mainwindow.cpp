#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
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


