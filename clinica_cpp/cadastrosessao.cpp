#include "cadastrosessao.h"
#include "ui_cadastrosessao.h"

cadastrosessao::cadastrosessao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastrosessao)
{
    ui->setupUi(this);
}

cadastrosessao::~cadastrosessao()
{
    delete ui;
}
