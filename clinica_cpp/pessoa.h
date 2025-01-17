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
        // Construtor
        explicit Pessoa(const QString& nome, const QString& cpf, const QString& contato,
                        const QString& email, const QDate& dataNascimento);

        // Destrutor
        ~Pessoa();

        // Métodos públicos
        int calcularIdade() const;

        // Getters
        QString getNome() const;
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
        // Construtor
        explicit Paciente(const QString& nome, const QString& cpf, const QString& contato,
                          const QString& email, const QDate& dataNascimento,
                          const QString& convenio, const QString& diagnostico);

        // Destrutor
        ~Paciente();

        // Métodos públicos
        bool salvarNoBanco();

    signals:
        // Sinal emitido quando um paciente é cadastrado
        void pacienteCadastrado(int id);

    private:
        QString convenio;
        QString diagnostico;
};



class Colaborador : public Pessoa {
    Q_OBJECT

    public:
        // Construtor
        explicit Colaborador(const QString& nome, const QString& cpf, const QString& contato,
                          const QString& email, const QDate& dataNascimento,
                          const QString& cargo);

        // Destrutor
        ~Colaborador();

        // Métodos públicos
        bool salvarNoBanco();

    signals:
        // Sinal emitido quando um paciente é cadastrado
        void colaboradorCadastrado(int id);

    private:
        QString cargo;
    };

#endif // PESSOA_H
