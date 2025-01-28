#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>
#include <QDebug>
#include <QCoreApplication>

class Conexao {
public:

    Conexao();

    void fechar();
    bool abrir();
    QSqlDatabase getbancoDeDados() const ;

private:

    QSqlDatabase bancoDeDados;
    QString local, banco;

};

#endif // CONEXAO_H
