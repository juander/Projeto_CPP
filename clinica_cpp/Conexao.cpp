#include "Conexao.h"

Conexao::Conexao(){
    // Obtém o diretório da aplicação
    local = qApp->applicationDirPath();

    // Define o caminho do banco de dados
    banco = local + "\\banco_clinica.db";

    // Configura o tipo de banco de dados (SQLite neste caso)
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName(banco);
}

void Conexao::fechar() {
    if(bancoDeDados.isOpen()){
        bancoDeDados.close();
        qDebug() << "Conexão com o banco encerrada";
    }
}
bool Conexao::abrir(){
    bancoDeDados.setDatabaseName(banco);                                                                            // CRIANDO CONEXÃO COM O BANCO

    // Verificação da conexão com o banco de dados
    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao conectar com o banco de dados" << bancoDeDados.lastError().text();
        return false;
    }else{
        qDebug() << "Banco conectado com sucesso";
        return true;
    }
}

QSqlDatabase Conexao::getbancoDeDados() const {
    return bancoDeDados;
}

