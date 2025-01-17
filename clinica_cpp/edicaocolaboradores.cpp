#include "edicaocolaboradores.h"
#include "ui_edicaocolaboradores.h"

edicaoColaboradores::edicaoColaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edicaoColaboradores)
{
    ui->setupUi(this);
}

edicaoColaboradores::~edicaoColaboradores()
{
    delete ui;
}
