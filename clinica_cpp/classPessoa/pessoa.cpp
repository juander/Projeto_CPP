#include "pessoa.h"

Pessoa::Pessoa(const QString& nome, const QString& cpf, const QString& contato,
               const QString& email, const QDate& dataNascimento)
    : nome(nome), cpf(cpf), contato(contato), email(email), dataNascimento(dataNascimento) {} // Construtor

Pessoa::~Pessoa() {}                                                                          // Destrutor

int Pessoa::calcularIdade() const {
    QDate hoje = QDate::currentDate();
    int idade = hoje.year() - dataNascimento.year();

    if ((hoje.month() < dataNascimento.month()) ||                                            // Ajusta a idade se o aniversário ainda não aconteceu neste ano
        (hoje.month() == dataNascimento.month() && hoje.day() < dataNascimento.day())) {
        idade--;
    }

    return idade;
}

///////////////////////////////////////////////////////////////////

QString Pessoa::getNome() const { return nome; }
QString Pessoa::getCpf() const { return cpf; }
QString Pessoa::getContato() const { return contato; }                                        // Getters
QString Pessoa::getEmail() const { return email; }
QDate Pessoa::getDataDeNascimento() const { return dataNascimento; }

Paciente::Paciente(const QString& nome, const QString& cpf, const QString& contato,
                   const QString& email, const QDate& dataNascimento,
                   const QString& convenio, const QString& diagnostico)
    : Pessoa(nome, cpf, contato, email, dataNascimento), convenio(convenio), diagnostico(diagnostico) {} // Construtor

Paciente::~Paciente() {}                                                                      // Destrutor

///////////////////////////////////////////////////////////////////

bool Paciente::salvarNoBanco() {
    QString nasc = dataNascimento.toString("dd/MM/yyyy");                                     // Converte a data de nascimento para string no formato QString

    QSqlQuery query;
    query.prepare("INSERT INTO tb_pacientes (nome, idade, cpf, diagnostico_pre, contato, email, convenio_plano, data_nasc) "
                  "VALUES (:nome, :idade, :cpf, :diagnostico_pre, :contato, :email, :convenio_plano, :data_nasc)");

    query.bindValue(":nome", getNome());
    query.bindValue(":idade", calcularIdade());                                               // Usando o método de calculo de idade para enviar a idade para o banco
    query.bindValue(":cpf", getCpf());
    query.bindValue(":diagnostico_pre", diagnostico);
    query.bindValue(":contato", getContato());
    query.bindValue(":email", getEmail());
    query.bindValue(":convenio_plano", convenio);
    query.bindValue(":data_nasc", nasc);

    if (query.exec()) {
        int Id_novo = query.lastInsertId().toInt();                                           // Obtendo o último ID inserido que acabou de ser gerado ao cadastrar
        emit pacienteCadastrado(Id_novo);                                                     // Emitindo um sinal para a janela de cadastro, para propagá-lo até a janela principal
        return true;
    } else {
        qDebug() << "Erro ao cadastrar no banco:" << query.lastError().text();
        return false;
    }
}

///////////////////////////////////////////////////////////////////

Colaborador::Colaborador(const QString& nome, const QString& cpf, const QString& contato,
                         const QString& email, const QDate& dataNascimento,
                         const QString& cargo)
    : Pessoa(nome, cpf, contato, email, dataNascimento), cargo(cargo) {}                      // Construtor

Colaborador::~Colaborador() {
    qDebug() << "Colaborador destruído";                                                      // Destrutor
}

///////////////////////////////////////////////////////////////////

bool Colaborador::salvarNoBanco() {
    QString nasc = dataNascimento.toString("dd/MM/yyyy");                                     // Converte a data de nascimento para string no formato QString

    QSqlQuery query;
    query.prepare("INSERT INTO tb_colaboradores (nome, idade, cpf, cargo, contato, email, data_nasc) "
                  "VALUES (:nome, :idade, :cpf, :cargo, :contato, :email, :data_nasc)");

    query.bindValue(":nome", getNome());
    query.bindValue(":idade", calcularIdade());                                               // Usando o método de calculo de idade para enviar a idade para o banco
    query.bindValue(":cpf", getCpf());
    query.bindValue(":cargo", cargo);
    query.bindValue(":contato", getContato());
    query.bindValue(":email", getEmail());
    query.bindValue(":data_nasc", nasc);

    if (query.exec()) {
        int Id_novo = query.lastInsertId().toInt();                                           // Obtendo o último ID inserido que acabou de ser gerado ao cadastrar
        emit colaboradorCadastrado(Id_novo);                                                  // Emitindo um sinal para a janela de cadastro, para propagá-lo até a janela principal
        return true;
    } else {
        qDebug() << "Erro ao cadastrar no banco:" << query.lastError().text();
        return false;
    }
}
