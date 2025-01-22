#include "cadastrosessao.h"
#include "ui_cadastrosessao.h"

cadastroSessao::cadastroSessao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroSessao)
{
    ui->setupUi(this);
}

cadastroSessao::~cadastroSessao()
{
    delete ui;
}
