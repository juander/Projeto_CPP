<<<<<<< HEAD
#ifndef EDICAOPACIENTE_H
#define EDICAOPACIENTE_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class edicaopaciente;
}

class edicaopaciente : public QDialog
{
    Q_OBJECT

public:
    explicit edicaopaciente(QWidget *parent = nullptr, int id_paciente = 0);
    ~edicaopaciente();

private slots:
    void on_editar_clicked();

    void on_cancelarEdit_clicked();

private:
    Ui::edicaopaciente *ui;
};

#endif // EDICAOPACIENTE_H
=======
#ifndef EDICAOPACIENTE_H
#define EDICAOPACIENTE_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class edicaopaciente;
}

class edicaopaciente : public QDialog
{
    Q_OBJECT

public:
    explicit edicaopaciente(QWidget *parent = nullptr, int id_paciente = 0);
    ~edicaopaciente();

private slots:
    void on_editar_clicked();

private:
    Ui::edicaopaciente *ui;
};

#endif // EDICAOPACIENTE_H
>>>>>>> 762b877 (Night update)
