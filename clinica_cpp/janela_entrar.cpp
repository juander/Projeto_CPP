#include "janela_entrar.h"
#include "ui_janela_entrar.h"

janela_entrar::janela_entrar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janela_entrar)
{
    ui->setupUi(this);
}

janela_entrar::~janela_entrar()
{
    delete ui;
}
