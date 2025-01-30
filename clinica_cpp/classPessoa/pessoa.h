#ifndef PESSOA_H
#define PESSOA_H

#include <QString>
#include <QDate>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

class Pessoa : public QObject {
    Q_OBJECT

    public:
        explicit Pessoa(const QString& nome, const QString& cpf, const QString& contato,
                        const QString& email, const QDate& dataNascimento);                // Construtor

        ~Pessoa();                                                                         // Destrutor

        int calcularIdade() const;                                                         // Método público

        QString getNome() const;                                                           // Getters
        QString getCpf() const;
        QString getContato() const;
        QString getEmail() const;
        QDate getDataDeNascimento() const;

    protected:
        QString nome;
        QString cpf;
        QString contato;
        QString email;
        QDate dataNascimento;
};

class Paciente : public Pessoa {
    Q_OBJECT

    public:
        explicit Paciente(const QString& nome, const QString& cpf, const QString& contato,
                          const QString& email, const QDate& dataNascimento,
                          const QString& convenio, const QString& diagnostico);            // Construtor

        ~Paciente();                                                                       // Destrutor

        bool salvarNoBanco();                                                              // Método público

    signals:
        void pacienteCadastrado(int id);                                                   // Sinal emitido quando um paciente é cadastrado

    private:
        QString convenio;
        QString diagnostico;
};

class Colaborador : public Pessoa {
    Q_OBJECT

    public:
        explicit Colaborador(const QString& nome, const QString& cpf, const QString& contato,
                             const QString& email, const QDate& dataNascimento,
                             const QString& cargo);                                        // Construtor

        ~Colaborador();                                                                    // Destrutor

        bool salvarNoBanco();                                                              // Método público

    signals:
        void colaboradorCadastrado(int id);                                                // Sinal emitido quando um colaborador é cadastrado

    private:
        QString cargo;
};

#endif // PESSOA_H
