#include "cadastrocolaboradores.h"
#include "ui_cadastrocolaboradores.h"

cadastroColaboradores::cadastroColaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroColaboradores)
{
    ui->setupUi(this);
}

cadastroColaboradores::~cadastroColaboradores()
{
    delete ui;
}
