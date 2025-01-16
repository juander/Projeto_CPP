#ifndef PESSOA_H
#define PESSOA_H

#include <QString>
#include <QDate>

class Pessoa
{
public:
    Pessoa(const QString &nome, const QString &idade, const QString &cpf, const QString &email, QString &numero, QDate &nascimento);
    //virtual ~Pessoa();

    QString getNome() const;
    QString getIdade() const;
    QString getCpf() const;
    QString getEmail() const;
    QString getNumero() const;
    QDate getNascimento() const;

protected:
    QString nome;
    QString idade;
    QString cpf;
    QString email;
    QString numero;
    QDate nascimento;
};

class Paciente : public Pessoa
{
public:
    Paciente(const QString &nome, const QString &idade, const QString &cpf, const QString &email, QString &numero, QDate &nascimento, QString &convenio_plano, QString diagnostico);
    //virtual ~Paciente();

private:
    QString convenio_plano;
    QString diagnostico;
};

#endif // PESSOA_H
