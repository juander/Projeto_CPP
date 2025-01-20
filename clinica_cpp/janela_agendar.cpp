#include "janela_agendar.h"
#include "ui_janela_agendar.h"

janela_agendar::janela_agendar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janela_agendar)
{
    ui->setupUi(this);
}

janela_agendar::~janela_agendar()
{
    delete ui;
}
