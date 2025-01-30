#include "Conexao.h"

Conexao::Conexao(){
    local = qApp->applicationDirPath();             // Obtém o diretório da aplicação
    banco = local + "\\banco_clinica.db";           // Define o caminho do banco de dados
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE"); // Configura o tipo de banco de dados (SQLite neste caso)
    bancoDeDados.setDatabaseName(banco);            // Define o nome do banco de dados
}

void Conexao::fechar() {
    if(bancoDeDados.isOpen()){
        bancoDeDados.close();                       // Fecha a conexão com o banco de dados
        qDebug() << "Conexão com o banco encerrada";
    }
}

bool Conexao::abrir(){
    bancoDeDados.setDatabaseName(banco);            // Define o nome do banco de dados

    if (!bancoDeDados.open()) {                     // Verificação da conexão com o banco de dados
        qDebug() << "Erro ao conectar com o banco de dados" << bancoDeDados.lastError().text();
        return false;                               // Retorna falso se a conexão falhar
    }else{
        qDebug() << "Banco conectado com sucesso";
        return true;                                // Retorna verdadeiro se a conexão for bem-sucedida
    }
}

QSqlDatabase Conexao::getbancoDeDados() const {
    return bancoDeDados;                            // Retorna o objeto do banco de dados
}

