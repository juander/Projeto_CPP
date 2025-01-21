#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>

class Conexao {
public:

    QSqlDatabase bancoDeDados;
    QString local, banco;

    Conexao(){
        local = qApp->applicationDirPath();
        banco = local + "\\banco_clinica.db";
        bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    }

    void fechar() {
        bancoDeDados.close();
    }
    bool abrir(){
        bancoDeDados.setDatabaseName(banco);                                                                            // CRIANDO CONEXÃO COM O BANCO

        // Verificação da conexão com o banco de dados
        if (!bancoDeDados.open()) {
            return false;
        }else{
            return true;
        }
    }
    bool aberto(){
        if(bancoDeDados.isOpen()) {
            return true;
        }else{
            return false;
        }
    }

};

#endif // CONEXAO_H
