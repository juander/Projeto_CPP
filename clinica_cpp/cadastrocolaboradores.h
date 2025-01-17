#ifndef CADASTROCOLABORADORES_H
#define CADASTROCOLABORADORES_H

#include <QDialog>
#include <QtSql>

#include "pessoa.h"

namespace Ui {
class cadastroColaboradores;
}

class cadastroColaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroColaboradores(QWidget *parent = nullptr);
    ~cadastroColaboradores();

private:
    Ui::cadastroColaboradores *ui;
};

#endif // CADASTROCOLABORADORES_H
