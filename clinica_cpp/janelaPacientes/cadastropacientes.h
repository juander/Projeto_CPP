#ifndef CADASTROPACIENTES_H
#define CADASTROPACIENTES_H

#include <QDialog>
#include <QtSql>

#include "../classPessoa/pessoa.h"

namespace Ui {
class cadastroPacientes;
}

class cadastroPacientes : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroPacientes(QWidget *parent = nullptr, const QString &modo = "Cadastrar", int id_paciente = -1);
    ~cadastroPacientes();

    void setIdPaciente(int id = -1);

    int getIdPaciente();

private slots:

    // Método para cadastrar um novo paciente
    void on_btnCadastrarPac_clicked();

    // Método para cancelar o cadastro    
    void on_btnCancelarPac_clicked();

private:
    Ui::cadastroPacientes *ui;
    QString tipoUso;
    int idPaciente;

    // Método para definir o modo da janela (Cadastrar ou Editar)
    void setModo(const QString &modo, int id_paciente);

signals:
    // Sinal emitido quando um paciente é cadastrado
    void pacienteCadastrado(int id);
};

#endif // CADASTROPACIENTES_H
