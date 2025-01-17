#ifndef EDICAOCOLABORADORES_H
#define EDICAOCOLABORADORES_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

#include "pessoa.h"

namespace Ui {
class edicaoColaboradores;
}

class edicaoColaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit edicaoColaboradores(QWidget *parent = nullptr, int id_colaborador = 0);
    ~edicaoColaboradores();

private slots:
    void on_editar_clicked();

    void on_cancelarEdit_clicked();

private:
    Ui::edicaoColaboradores *ui;
};

#endif // EDICAOCOLABORADORES_H
