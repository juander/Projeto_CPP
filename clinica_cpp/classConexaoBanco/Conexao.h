#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>
#include <QDebug>
#include <QCoreApplication>

class Conexao {
public:
    Conexao();                                      // Construtor
    void fechar();                                  // Método para fechar a conexão
    bool abrir();                                   // Método para abrir a conexão
    QSqlDatabase getbancoDeDados() const;           // Método para obter o banco de dados

private:
    QSqlDatabase bancoDeDados;                      // Objeto do banco de dados
    QString local, banco;                           // Strings para local e banco de dados
};

#endif // CONEXAO_H
