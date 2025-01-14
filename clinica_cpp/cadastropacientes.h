#ifndef CADASTROPACIENTES_H
#define CADASTROPACIENTES_H

#include <QDialog>

namespace Ui {
class cadastroPacientes;
}

class cadastroPacientes : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroPacientes(QWidget *parent = nullptr);
    ~cadastroPacientes();

private:
    Ui::cadastroPacientes *ui;
};

#endif // CADASTROPACIENTES_H
