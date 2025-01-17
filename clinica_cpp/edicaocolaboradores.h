#ifndef EDICAOCOLABORADORES_H
#define EDICAOCOLABORADORES_H

#include <QDialog>

namespace Ui {
class edicaoColaboradores;
}

class edicaoColaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit edicaoColaboradores(QWidget *parent = nullptr);
    ~edicaoColaboradores();

private:
    Ui::edicaoColaboradores *ui;
};

#endif // EDICAOCOLABORADORES_H
