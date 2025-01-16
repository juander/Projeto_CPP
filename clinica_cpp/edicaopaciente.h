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
    // Método para editar um paciente
    void on_editar_clicked();
    // Método para cancelar a edição
    void on_cancelarEdit_clicked();

private:
    Ui::edicaopaciente *ui;
};

#endif // EDICAOPACIENTE_H

