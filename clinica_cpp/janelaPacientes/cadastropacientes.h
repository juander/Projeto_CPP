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
    Q_OBJECT                                                                                                        // Macro Q_OBJECT

public:
    explicit cadastroPacientes(QWidget *parent = nullptr, const QString &modo = "Cadastrar", int id_paciente = -1); // Construtor
    ~cadastroPacientes();                                                                                           // Destrutor

    void setIdPaciente(int id = -1);                                                                                // Define o ID do paciente
    int getIdPaciente();                                                                                            // Retorna o ID do paciente

private slots:
    void on_btnCadastrarPac_clicked();                                                                              // Método para cadastrar um novo paciente
    void on_btnCancelarPac_clicked();                                                                               // Método para cancelar o cadastro

private:
    Ui::cadastroPacientes *ui;                                                                                      // Interface do usuário
    QString tipoUso;                                                                                                // Tipo de uso (Cadastrar ou Editar)
    int idPaciente;                                                                                                 // ID do paciente

    void setModo(const QString &modo, int id_paciente);                                                             // Método para definir o modo da janela (Cadastrar ou Editar)

signals:
    void pacienteCadastrado(int id);                                                                                // Sinal emitido quando um paciente é cadastrado
};

#endif // CADASTROPACIENTES_H
