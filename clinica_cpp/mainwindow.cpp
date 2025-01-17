#include "mainwindow.h"
#include "./ui_mainwindow.h"

// DEFINIÇÃO DA JANELA PRINCIPAL, QUE INCLUEM AS TABLEWIDGETS E SEUS BOTÕES

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                                                                                              // CONSTRUTOR

    // Configuração do banco de dados SQLite
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName("..\\..\\banco_clinica.db");                                                       // CRIANDO CONEXÃO COM O BANCO

    // Verificação da conexão com o banco de dados
    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao abrir o banco de dados:" << bancoDeDados.lastError().text();                           // CONFERINDO SE O BANCO FOI CONECTADO
    } else {
        qDebug() << "Banco de dados conectado com sucesso!";
    }

    // Adicionando efeito de sombra ao frame superior
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);                                  // EFEITOS DE COMBRA NA PARTE SUPERIOR DA JANELA
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0, 5);
    ui->frame->setGraphicsEffect(shadowEffect);
}

MainWindow::~MainWindow()
{
    delete ui;                                                                                                      // DESTRUTOR
}





// MÉTODO PARA ACESSAR A PÁGINA "AGENDA"

void MainWindow::on_btnAgenda_clicked()
{
    int index = ui->paginas->indexOf(ui->Agenda);                                                                   // PÁGINA AGENDA
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
}

// FIM DA PÁGINA AGENDA





// MÉTODO PARA ACESSAR A PÁGINA "ATENDIMENTO"

void MainWindow::on_btnAtendimento_clicked()
{
    int index = ui->paginas->indexOf(ui->Atendimento);                                                              // PÁGINA ATENDIMENTO
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
}

// FIM DA PÁGINA ATENDIMENTO





// MÉTODO PARA ACESSAR A PÁGINA "PACIENTES"

void MainWindow::on_btnPacientes_clicked()
{
    int index = ui->paginas->indexOf(ui->Pacientes);                                                                // PÁGINA PACIENTES
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes");                                                                    // ACESSANDO A TABELA NO BANCO

    if(query.exec()){
        setTabelaPacientes(query);                                                                                  // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
    }else{
        QMessageBox::warning(this, "ERRO", "Não foi possível acessar os pacientes no banco de dados");
    }
}


    // MÉTODOS DA PÁGINA DO PACIENTE:

    // MÉTODO DA DEFINIÇÃO DA TABLE

    void MainWindow::setTabelaPacientes(QSqlQuery &query)
    {
        int tb_linha = 0;

        // Limpa os dados antigos da tabela
        ui->tw_pacientes->clearContents();
        ui->tw_pacientes->setRowCount(0);  // Reseta as linhas

        ui->tw_pacientes->setColumnCount(9);                                                                        // SETA A TABLE EM 9 COLUNAS
        while(query.next()){

            ui->tw_pacientes->insertRow(tb_linha);

            for(int i = 0; i <= 8; i++){
                ui->tw_pacientes->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));              // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
            }
            ui->tw_pacientes->setRowHeight(tb_linha,20);

            tb_linha++;
        }

        // Setando a largura das colunas da tabela                                                                  // DEFINIÇÃO DA ESTRUTURA DA TABLE
        ui->tw_pacientes->setColumnWidth(0, 80);  // ID
        ui->tw_pacientes->setColumnWidth(1, 280); // Nome
        ui->tw_pacientes->setColumnWidth(2, 40);  // Idade
        ui->tw_pacientes->setColumnWidth(3, 135); // CPF
        ui->tw_pacientes->setColumnWidth(4, 150); // Diagnóstico
        ui->tw_pacientes->setColumnWidth(5, 124); // NºCelular
        ui->tw_pacientes->setColumnWidth(6, 180); // E-mail
        ui->tw_pacientes->setColumnWidth(7, 135); // Convênio/Plano
        ui->tw_pacientes->setColumnWidth(8, 70); // Nascimento

        QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
        ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
        ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_pacientes->verticalHeader()->setVisible(false);
        ui->tw_pacientes->setStyleSheet("QTableWidget::item:selected {background-color: blue}");                    // FIM DA DEFINIÇÃO
    }

    // MÉTODOS DE CADASTRO DO PACIENTE:

    // CADASTRANDO NOVO PACIENTE USANDO MÉTODOS PARA ATUALIZAR A TABLE EM TEMPO REAL

    void MainWindow::on_btnCadastroPac_clicked()
    {
        cadastroPacientes cadastramento(this);                                                                         // CRIANDO A JANELA DE CADASTRO

        // O SINAL QUE TRAZ O ID DO PACIENTE CADASTRADO PARA JANELA
        bool connected = connect(&cadastramento, &cadastroPacientes::pacienteCadastrado,                               // PRINCIPAL É EMITIDO PELO OBJETO PACIENTE, QUE É O ÚNICO QUE
                                 this, &MainWindow::adicionarPacienteNaTabela);                                        // TEM ACESSO DIRETO A QUERY DE INSERT, PARA A JANELA DE
        if (!connected) {                                                                                              // CADASTRO E POR FIM PARA ESSA JANELA PRINCIPAL QUE ACESSA O MÉTODO
            qDebug() << "Erro ao conectar o sinal pacienteCadastrado";                                                 // DE ADICIONAR O PACIENTE NA TABLE
        }                                                                                                              //            |
        cadastramento.exec();                                                                                          //            |
    }                                                                                                                  //            |
    //                                                                                                                               |
    // MÉTODO PARA CARREGAR NOVO PACIENTE CADASTRADO NA TABELA AUTOMATICAMENTE A PARTIR DO ID GERADO NO BANCO                        |
    //                                                                                                                               |
    void MainWindow::adicionarPacienteNaTabela(int id)                                                        //    <----------------
    {
        QSqlQuery query;                                                                                               // ESSE MÉTODO SÓ SERÁ USADO QUANDO A CONEXÃO RETORNAR TRUE, OU SEJA, QUANDO O PACIENTE FOR CADASTRADO
        query.prepare("SELECT * FROM tb_pacientes WHERE id = :id");                                                    // FAZENDO A QUERY SELECT COM O NOVO ID VINDO DAS CONEXÕES

        query.bindValue(":id", id);

        if(query.exec() && query.first()){
            int linha = ui->tw_pacientes->rowCount();
            ui->tw_pacientes->insertRow(linha);                                                                        // ADICIONANDO UMA NOVA LINHA NA TABLE
            for(int i = 0; i <= 8; i++){
                ui->tw_pacientes->setItem(linha, i, new QTableWidgetItem(query.value(i).toString()));                  // ATUALIZANDO A TABLE
            }
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao carregar o novo paciente.");
        }
    }
    //
    // MÉTODO DE APAGAR PACIENTE
    //
    void MainWindow::on_btnApagarPac_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_pacientes->currentRow() == -1) {
            QMessageBox::warning(nullptr, "Aviso", "Nenhuma paciente foi selecionado.");                               // CONFERINDO SE ALGUM PACIENTE FOI SELECIONADO
            return;
        }
        // Verificando qual é a linha selecionada e descobrindo o id dela
        int linha = ui->tw_pacientes->currentRow();                                                                    // ARMAZENANDO A LINHA SELECIONADA
        QString id = ui->tw_pacientes->item(linha, 0)->text();                                                         // ARMAZENANDO O ID DO PACIENTE SELECIONADO

        // Query para excluir
        QSqlQuery query;
        query.prepare("DELETE FROM tb_pacientes WHERE id="+id);                                                        // DELETANDO O PACIENTE DO BANCO DE DADOS

        if(query.exec()){
            // Removendo a linha do Table
            ui->tw_pacientes->removeRow(linha);
            QMessageBox::information(this,"","Excluído");                                                              // REMOVENDO LINHA DA TABLE E GERANDO O POP-UP
        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao excluir registro");
        }
    }
    //
    // MÉTODO DE EDITAR PACIENTE
    //
    void MainWindow::on_btnEditarPac_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_pacientes->currentRow() == -1) {
            QMessageBox::warning(nullptr, "Aviso", "Nenhuma paciente foi selecionado.");                                // CONFERINDO SE ALGUM PACIENTE FOI SELECIONADO
            return;
        }
        int linha = ui->tw_pacientes->currentRow();                                                                     // ARMAZENANDO A LINHA SELECIONADA
        int id = ui->tw_pacientes->item(linha, 0)->text().toInt();                                                      // ARMAZENANDO O ID DO PACIENTE SELECIONADO

        edicaopaciente editarPaciente(this, id);                                                                        // CRIANDO A JENELA DE EDITAR PACIENTE
        editarPaciente.exec();

        // Carregar paciente na Table novamente
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_pacientes WHERE id="+QString::number(id));                                      // QUERY SELECT PARA BUSCAR O PACIENTE PELO ID

        if(query.exec() && query.first()){
            for(int i = 1; i <= 8; i++){
                ui->tw_pacientes->setItem(linha,i,new QTableWidgetItem(query.value(i).toString()));                     // ATUALIZANDO A TABLE COM A EDIÇÃO DO PACIENTE NO BANCO
            }
        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao atualizar paciente na tabela");
        }
    }
    //
    // MÉTODO DE PESQUISA DE PACIENTE PELO NOME
    //
    void MainWindow::on_linePesquisaPac_textChanged(const QString &arg1)
    {
        QString nome = ui->linePesquisaPac->text(); // Pegando o texto do linePesquisaPac                               // MÉTODO SLOT DO QT PARA RECONHCER O QUE ESTÁ SENDO DIGITADO NA LINHA EM TEMPO REAL

        QSqlQuery query;
        query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");                                              // FAZENDO A QUERY DE SELECT PELO NOME
        query.bindValue(":nome", nome + "%");

        if(query.exec()){
            setTabelaPacientes(query);                                                                                  // SETANDO A TABLE EM TEMPO REAL
        }else{
            QMessageBox::warning(this, "ERRO", "Não foi possível acessar os pacientes no banco de dados");
        }
    }

// FIM PÁGINA PACIENTES





// MÉTODO PARA ACESSAR A PÁGINA "COLABORADORES"

void MainWindow::on_btnColaboradores_clicked()
{
    int index = ui->paginas->indexOf(ui->Colaboradores);                                                            // PÁGINA COLABORADORES
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_colaboradores");                                                                // ACESSANDO A TABELA NO BANCO

    if(query.exec()){
        setTabelaColaboradores(query);                                                                              // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
    }else{
        QMessageBox::warning(this, "ERRO", "Não foi possível acessar os colaboradores no banco de dados");
    }
}

    // MÉTODOS DA PÁGINA DO COLABORADOR:

    // MÉTODO DA DEFINIÇÃO DA TABLE

    void MainWindow::setTabelaColaboradores(QSqlQuery &query)
    {
        int tb_linha = 0;

        // Limpa os dados antigos da tabela
        ui->tw_colaboradores->clearContents();
        ui->tw_colaboradores->setRowCount(0);  // Reseta as linhas

        ui->tw_colaboradores->setColumnCount(8);                                                                    // SETA A TABLE EM 8 COLUNAS
        while(query.next()){

            ui->tw_colaboradores->insertRow(tb_linha);

            for(int i = 0; i <= 7; i++){
                ui->tw_colaboradores->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));          // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
            }
            ui->tw_colaboradores->setRowHeight(tb_linha,20);

            tb_linha++;
        }

        // Setando a largura das colunas da tabela                                                                  // DEFINIÇÃO DA ESTRUTURA DA TABLE
        ui->tw_colaboradores->setColumnWidth(0, 80);  // ID
        ui->tw_colaboradores->setColumnWidth(1, 280); // Nome
        ui->tw_colaboradores->setColumnWidth(2, 40);  // Idade
        ui->tw_colaboradores->setColumnWidth(3, 135); // CPF
        ui->tw_colaboradores->setColumnWidth(4, 160); // Cargo
        ui->tw_colaboradores->setColumnWidth(5, 144); // NºCelular
        ui->tw_colaboradores->setColumnWidth(6, 180); // E-mail
        ui->tw_colaboradores->setColumnWidth(7, 70);  // Nascimento

        QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Cargo", "NºCelular", "E-mail", "Nascimento"};
        ui->tw_colaboradores->setHorizontalHeaderLabels(cabecalho);
        ui->tw_colaboradores->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_colaboradores->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_colaboradores->verticalHeader()->setVisible(false);
        ui->tw_colaboradores->setStyleSheet("QTableWidget::item:selected {background-color: blue}");                // FIM DA DEFINIÇÃO
    }

    void MainWindow::on_btnCadastroCol_clicked()
    {
        cadastroColaboradores cadastramento(this);                                                                     // CRIANDO A JANELA DE CADASTRO

        // O SINAL QUE TRAZ O ID DO COLABORADOR CADASTRADO PARA JANELA
        bool connected = connect(&cadastramento, &cadastroColaboradores::colaboradorCadastrado,                        // PRINCIPAL É EMITIDO PELO OBJETO COLABORADOR, QUE É O ÚNICO QUE
                                 this, &MainWindow::adicionarColaboradorNaTabela);                                  // TEM ACESSO DIRETO A QUERY DE INSERT, PARA A JANELA DE
        if (!connected) {                                                                                              // CADASTRO E POR FIM PARA ESSA JANELA PRINCIPAL QUE ACESSA O MÉTODO
            qDebug() << "Erro ao conectar o sinal colaboradorCadastrado";                                              // DE ADICIONAR O COLABORADOR NA TABLE
        }                                                                                                              //            |
        cadastramento.exec();                                                                                          //            |
    }                                                                                                                  //            |
    //                                                                                                                               |
    // MÉTODO PARA CARREGAR NOVO COLABORADOR CADASTRADO NA TABELA AUTOMATICAMENTE A PARTIR DO ID GERADO NO BANCO                     |
    //                                                                                                                               |
    void MainWindow::adicionarColaboradorNaTabela(int id)                                                              // <----------
    {
        QSqlQuery query;                                                                                               // ESSE MÉTODO SÓ SERÁ USADO QUANDO A CONEXÃO RETORNAR TRUE, OU SEJA, QUANDO O COLABORADOR FOR CADASTRADO
        query.prepare("SELECT * FROM tb_colaboradores WHERE id = :id");                                                // FAZENDO A QUERY SELECT COM O ID DO NOVO COLABORADOR VINDO DO SIGNAL PROPAGADO PELO OBJETO
        query.bindValue(":id", id);

        if(query.exec() && query.first()){
            int linha = ui->tw_colaboradores->rowCount();
            ui->tw_colaboradores->insertRow(linha);                                                                    // ADICIONANDO LINHA NA TABLE
            for(int i = 0; i <= 7; i++){
                ui->tw_colaboradores->setItem(linha, i, new QTableWidgetItem(query.value(i).toString()));              // CARREGANDO A TABLE COM OS DADOS DO BANCO
            }
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao carregar o novo colaborador.");
        }
    }
    //
    // MÉTODO DE APAGAR COLABORADOR
    //
    void MainWindow::on_btnApagarCol_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_colaboradores->currentRow() == -1) {
            QMessageBox::warning(nullptr, "Aviso", "Nenhuma colaborador foi selecionado.");                             // CONFERINDO SE ALGUM COLABORADOR  FOI SELECIONADO
            return;
        }
        // Verificando qual é a linha selecionada e descobrindo o id dela
        int linha = ui->tw_colaboradores->currentRow();                                                                 // ARMAZENANDO A LINHA SELECIONADA
        QString id = ui->tw_colaboradores->item(linha, 0)->text();                                                      // ARMAZENANDO O ID DO COLABORADOR  SELECIONADO

        // Query para excluir
        QSqlQuery query;
        query.prepare("DELETE FROM tb_colaboradores WHERE id="+id);                                                     // DELETANDO O COLABORADOR DO BANCO DE DADOS

        if(query.exec()){
            // Removendo a linha do Table
            ui->tw_colaboradores->removeRow(linha);
            QMessageBox::information(this,"","Excluído");                                                               // REMOVENDO LINHA DA TABLE E GERANDO O POP-UP
        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao excluir registro");
        }
    }
    //
    // MÉTODO DE EDITAR COLABORADOR
    //
    void MainWindow::on_btnEditarCol_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_colaboradores->currentRow() == -1) {
            QMessageBox::warning(nullptr, "Aviso", "Nenhuma colaborador foi selecionado.");                             // CONFERINDO SE ALGUM COLABORADOR FOI SELECIONADO
            return;
        }
        int linha = ui->tw_colaboradores->currentRow();                                                                 // ARMAZENANDO A LINHA SELECIONADA
        int id = ui->tw_colaboradores->item(linha, 0)->text().toInt();                                                  // ARMAZENANDO O ID DO COLABORADOR SELECIONADO

        edicaoColaboradores editarColaborador(this, id);                                                                // CRIANDO A JENELA DE EDITAR COLABORADOR
        editarColaborador.exec();

        // Carregar colaborador na Table novamente
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_colaboradores WHERE id="+QString::number(id));                                  // QUERY SELECT PARA BUSCAR O COLABORADOR PELO ID

        if(query.exec() && query.first()){
            for(int i = 1; i <= 8; i++){
                ui->tw_colaboradores->setItem(linha,i,new QTableWidgetItem(query.value(i).toString()));                 // ATUALIZANDO A TABLE COM A EDIÇÃO DO COLABORADOR NO BANCO
            }
        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao atualizar colaborador na tabela");
        }
    }
    //
    // MÉTODO DE PESQUISAR COLABORADOR
    //
    void MainWindow::on_linePesquisaCol_textChanged(const QString &arg1)
    {
        QString nome = ui->linePesquisaCol->text(); // Pegando o texto do linePesquisaPac                               // MÉTODO SLOT DO QT PARA RECONHCER O QUE ESTÁ SENDO DIGITADO NA LINHA EM TEMPO REAL

        QSqlQuery query;
        query.prepare("SELECT * FROM tb_colaboradores WHERE nome LIKE :nome");                                          // FAZENDO A QUERY DE SELECT PELO NOME
        query.bindValue(":nome", nome + "%");

        if(query.exec()){
            setTabelaColaboradores(query);                                                                              // SETANDO A TABLE EM TEMPO REAL
        }else{
            QMessageBox::warning(this, "ERRO", "Não foi possível acessar os colaboradores no banco de dados");
        }
    }


// FIM PÁGINA COLABORADORES




// MÉTODO PARA ACESSAR A PÁGINA "RELATÓRIOS"

void MainWindow::on_btnRelatorios_clicked()
{
    int index = ui->paginas->indexOf(ui->Relatorios);                                                               // PÁGINA RELATÓRIOS
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
}

// FIM DA PÁGINA RELATÓRIOS





// MÉTODO PARA ACESSAR A PÁGINA "FORNECEDORES"

void MainWindow::on_btnFornecedores_clicked()
{
    int index = ui->paginas->indexOf(ui->Fornecedores);                                                             // PÁGINA FORNECEDORES
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
}

// FIM DA PÁGINA FORNCEDORES
