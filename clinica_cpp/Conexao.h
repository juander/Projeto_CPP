#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>


class Conexao {
public:
    QSqlDatabase bancoDeDados;
    Conexao(){
        bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    }

    void fechar() {
        bancoDeDados.close();
    }
    bool abrir(){
        QString local = qApp->applicationDirPath();
        QString banco = local + "\\banco_clinica.db";
        bancoDeDados.setDatabaseName(banco);                                                                            // CRIANDO CONEXÃO COM O BANCO

        // Verificação da conexão com o banco de dados
        if (!bancoDeDados.open()) {
            return false;
        }else{
            return true;
        }
    }

};

#endif // CONEXAO_H
