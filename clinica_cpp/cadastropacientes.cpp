#include "cadastropacientes.h"
#include "ui_cadastropacientes.h"

cadastroPacientes::cadastroPacientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroPacientes)
{
    ui->setupUi(this);
}

cadastroPacientes::~cadastroPacientes()
{
    delete ui;
}
