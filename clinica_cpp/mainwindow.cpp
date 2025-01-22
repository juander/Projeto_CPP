#include "mainwindow.h"
#include "./ui_mainwindow.h"

// DEFINIÇÃO DA JANELA PRINCIPAL, QUE INCLUEM AS TABLEWIDGETS E SEUS BOTÕES

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                                                                                              // CONSTRUTOR

}

MainWindow::~MainWindow()
{
    delete ui;                                                                                                      // DESTRUTOR
}



//////////////////////////////////////////

// MÉTODO PARA SETAR A PALETA DE CORES DO SISTEMA PARA CLARO EM QUALQUER DISPOSITIVO

void MainWindow::setPaletaCor(QApplication &app){
    // Definir o estilo Fusion
    app.setStyle(QStyleFactory::create("Fusion"));

    // Definir uma paleta clara personalizada
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 255, 255));          // Fundo branco
    palette.setColor(QPalette::WindowText, QColor(0, 0, 0));            // Texto preto
    palette.setColor(QPalette::Base, QColor(255, 255, 255));            // Fundo de widgets (ex: QLineEdit)
    palette.setColor(QPalette::AlternateBase, QColor(240, 240, 240));   // Cor alternativa de fundo
    palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
    palette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));
    palette.setColor(QPalette::Text, QColor(0, 0, 0));                  // Texto
    palette.setColor(QPalette::Button, QColor(240, 240, 240));          // Cor de fundo do botão
    palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));            // Cor do texto do botão
    palette.setColor(QPalette::BrightText, QColor(255, 0, 0));

    app.setPalette(palette);                                            // Setando a peleta no app
}


//////////////////////////////////////////


// MÉTODO PARA FORMATAR A PÁGINA PRINCIPAL E DEFINIR A PÁGINA DE INÍCIO

void MainWindow::janelaFormatada(){
    ui->layoutPrincipal->setSpacing(0);                                                                             // SETANDO OS ESPAÇOS ENTRE OS LAYOUTS

    ui->paginas->tabBar()->setVisible(false);                                                                       // DEIXANDO OS ÍCONES DAS PÁGINAS DA TABWIDGET INVISÍVEIS

    // FORMATANDO O LAYOUT SUPERIOR

    ui->frameSuperior->setFixedHeight(ui->frameSuperior->height() + 40);  // Aumenta a altura vertical do QFrame

    ui->frameSuperior->setStyleSheet("QFrame {"
                                     "background-color: rgb(109, 176, 236);"  // Cor de fundo da barra lateral
                                     "border-top-left-radius: 10px;"  // Borda superior esquerda
                                     "border-top-right-radius: 10px;" // Borda superior direitaz
                                     "}");

    // Adicionando efeito de sombra ao frame superior
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);  // Aumentando o desfoque para 15px
    shadowEffect->setOffset(0, 7);  // Deslocando a sombra 10px para baixo
    shadowEffect->setColor(QColor(0, 0, 0, 150));  // Definindo cor da sombra com maior opacidade

    ui->frameSuperior->setGraphicsEffect(shadowEffect);

    // FORMATANDO O LAYOUT LATERAL

    ui->frameLateral->setStyleSheet("QFrame {"
                                    "background-color: rgb(109, 176, 236);"  // Cor de fundo da barra lateral
                                    "border-bottom-left-radius: 10px;"
                                    "}");

    ui->line1->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->line2->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->line3->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->line4->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->line5->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->line6->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->line7->setStyleSheet("QFrame {"
                             "border: 1px solid #000000;"                   // Cor de borda
                             "}");

    ui->frameSuperior->raise(); // Traz o frame para frente
    ui->frameLateral->lower(); // Envia o frame_2 para trás

    /////////////////////////////////////////////////

    // COLOCANDO IMAGENS NA JANELA PRINCIPAL

    QMovie *gif = new QMovie(":/icons/giftest.gif");                        // FAZENDO TESTE COM GIFS
    ui->labelGif->setMovie(gif);
    gif->start();

    /////////////////////////////////////////////////

    on_btnInicio_clicked();                                                                                         // DEFINI A PÁGINA INICIAL COMO SEMPRE A PRIMEIRA AO ABRIR O PROGRAMA

    logado = false;

}


//////////////////////////////////////////




// MÉTODO PARA REDIMENSIONAR AS TABELAS AUTOMATICAMENTE E CASO ALGO NÃO CAIBA EXIBIR O TEXTO COMPLETO AO COLOCAR O MOUSE EM CIMA

void MainWindow::redimensionarTable(QTableWidget* table){

    table->resizeColumnsToContents();  // Ajusta as colunas ao conteúdo

    // Agora, fazemos as colunas se expandirem para preencher a largura total da tabela
    for (int i = 0; i < table->columnCount(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Após redimensionar as colunas, fazemos o ajuste de layout
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Adicionando Tooltips para mostrar o conteúdo completo ao passar o mouse sobre a célula
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->item(row, col);
            if (item) {
                // Define o conteúdo completo da célula como o Tooltip
                item->setToolTip(item->text());
                // Alinha os itens das tabelas no centro das colunas
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

//////////////////////////////////////////

// MÉTODO PARA RESETAR O ESTILO DOS BOTÕES

void MainWindow::resetButtonStyles() {
    ui->btnAgenda->setStyleSheet("");
    ui->btnAtendimento->setStyleSheet("");
    ui->btnPacientes->setStyleSheet("");
    ui->btnColaboradores->setStyleSheet("");
    ui->btnFornecedores->setStyleSheet("");
    ui->btnRelatorios->setStyleSheet("");
    ui->btnInicio->setStyleSheet("");
}

//////////////////////////////////////////

// MÉTODO PARA ATUALIZAR O SISTEMA QUANDO O USUÁRIO LOGAR

void MainWindow::usuarioEntrou(){

    logado = true;                                                                                              // ESTADO DE LOGIN TRUE
    conexao.abrir();                                                                                            // ABRINDO A CONEXÃO COM O BANCO

    // Interface para usuário logado
    ui->btnEntrar->setText("Sair");
    ui->btnEntrar->setStyleSheet("background-color: darkred; color: white;");
    QPixmap icone(":/icons/Generic avatar.png");
    ui->iconPerfil->setPixmap(icone.scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->txtUsuario->setText(
        QString("<html><head/><body><p><span style=\" font-size:18pt; "
                "font-weight:700; color:#000000;\">%1</span></p></body></html>")

            .arg(nome_usuario)
        );
    ui->txtClinica->setText(
        QString("<html><head/><body><p><span style=\"font-size:18pt; "
                "font-weight:700;\">%1 -</span></p></body></html>")

            .arg(clinica_usuario)
        );
}

/////////////////////////////////////////

// MÉTODO PARA ATUALIZAR O SISTEMA QUANDO O USUÁRIO DESLOGAR

void MainWindow::usuarioSaiu(){

    logado = false;                                                                                               // ESTADO DE LOGIN FALSE
    conexao.fechar();                                                                                             // FECHANDO CONEXÃO COM O BANCO

    // Reseta a interface
    ui->btnEntrar->setText("Entrar");
    ui->btnEntrar->setStyleSheet("background-color: darkblue; color: white;");
    ui->iconPerfil->clear();
    ui->txtUsuario->clear();
    ui->txtClinica->setText(
        "<html><head/><body><p><span style=\"font-size:18pt; "
        "font-weight:700;\">NOME_CLÍNICA</span></p></body></html>"
        );

    // Atualiza outras partes da interface
    on_btnInicio_clicked();
    ui->tw_pacientes->setRowCount(0);
    ui->tw_pacientes->setColumnCount(0);
    ui->tw_colaboradores->setRowCount(0);
    ui->tw_colaboradores->setColumnCount(0);
}


//////////////////////////////////////////

// MÉTODO PARA ACESSAR A JANELA "ENTRAR"

void MainWindow::on_btnEntrar_clicked() {
    if (!logado) {                                                                                                   // NÃO LOGADO, LOGANDO
        janela_entrar janelaEntrar(this, &conexao);                                                                  // Passando a conexão para a janela de login
        janelaEntrar.exec();

        if (janelaEntrar.logadoJanela) {                                                                             // Verifica se o login foi bem-sucedido

            // Atualiza informações do usuário usando os dados emitidos pela janela_entrar
            id_usuario = janelaEntrar.id;
            nome_usuario = janelaEntrar.nome;
            clinica_usuario = janelaEntrar.clinica;
            cargo_usuario = janelaEntrar.cargo;

            usuarioEntrou();
        } else {
            conexao.fechar();
        }

    } else {                                                                                                        // LOGADO, SAINDO
        usuarioSaiu();
    }
}


/////////////////////////////////////////

// MÉTODO PARA ACESSAR A PÁGINA "INICIO"

void MainWindow::on_btnInicio_clicked()
{
    resetButtonStyles();
    ui->btnInicio->setStyleSheet("background-color: rgb(179, 213, 243);");                                          // ALTERAR A COR DE DESTAQUE DO BOTÃO
    ui->btnInicio->setAutoFillBackground(true);

    int index = ui->paginas->indexOf(ui->Inicio);                                                                   // PÁGINA INICIO
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
}

// FIM DA PÁGINA INICIO


///////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "AGENDA"

void MainWindow::on_btnAgenda_clicked()
{
    if(logado){
        resetButtonStyles();
        ui->btnAgenda->setStyleSheet("background-color: rgb(179, 213, 243);");                                            // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnAgenda->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Agenda);                                                                     // PÁGINA AGENDA
        ui->paginas->setCurrentIndex(index);

        QSqlQuery query;
        query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional");                          // ACESSANDO A TABELA NO BANCO
        query.bindValue(":id_profissional", id_usuario);

        if(query.exec()){
            setAgenda(query);                                                                                              // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
        }else{
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }

    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
    }
}

////////////////////////////////////////////////////////////////////

    // MÉTODOS DA PÁGINA "AGENDA"


    // MÉTODO DE PESQUISA

    void MainWindow::on_checkMinhaAgenda_stateChanged(int arg1)
    {
        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();
        qDebug() << "Minha agenda: " << filtrarMinhaAgenda;

        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo

        QSqlQuery query;

        if (filtrarMinhaAgenda){
            ui->lineEditAgenda->clear();

            query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional");
            query.bindValue(":id_profissional", id_usuario);

            ui->comboBoxAgenda->setCurrentIndex(0);
        } else {

            if(!filtrarData){
                query.prepare("SELECT * FROM tb_agendamentos");
            } else {

                QDate data = ui->calendarioAgenda->selectedDate();

                query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data");
                query.bindValue(":data", data);
            }
        }

        // Executa a query
        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }

    void MainWindow::on_comboBoxAgenda_currentTextChanged(const QString &arg1)
    {
        ui->lineEditAgenda->clear();

        QSqlQuery query;

        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();

        if (filtrarMinhaAgenda){
            query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional");
            query.bindValue(":id_profissional", id_usuario);

            ui->comboBoxAgenda->setCurrentIndex(0);

        } else {
            query.prepare("SELECT * FROM tb_agendamentos");
        }
        // Executa a query
        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }

    void MainWindow::on_lineEditAgenda_textChanged(const QString &arg1)
    {
        QString pesquisado = ui->lineEditAgenda->text(); // Pegando o texto do lineEditAgenda

        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo

        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();

        QSqlQuery query;

        if (!filtrarMinhaAgenda){


            if (!filtrarData) {

                if (pesquisado.isEmpty()) {
                    // Query padrão: Mostra apenas a agenda do profissional logado
                    query.prepare("SELECT * FROM tb_agendamentos");
                } else {
                    // Filtra conforme o texto digitado e a opção selecionada na comboBox
                    QString opcaoSelecionada = ui->comboBoxAgenda->currentText(); // Pega a opção selecionada no ComboBox

                    if (opcaoSelecionada == "Profissional") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional");
                        query.bindValue(":profissional", pesquisado + "%");

                    } else if (opcaoSelecionada == "Paciente") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente");
                        query.bindValue(":paciente", pesquisado + "%");

                    } else if (opcaoSelecionada == "Especialidade") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade");
                        query.bindValue(":especialidade", pesquisado + "%");
                    }
                }
            }
        } else {

            if (pesquisado.isEmpty()) {
                // Query padrão: Mostra apenas a agenda do profissional logado
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional");
                query.bindValue(":id_profissional", id_usuario);
            } else {
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE : paciente");
                query.bindValue(":id_profissional", id_usuario);
                query.bindValue(":paciente", pesquisado + "%");
            }
        }
        // Executa a query
        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }

    void MainWindow::on_checkDataAgenda_stateChanged(int arg1)
    {

    }

    void MainWindow::on_calendarioAgenda_clicked(const QDate &date)
    {
        atualizarTabelaPorData();
    }

    void MainWindow::atualizarTabelaPorData()
    {
        // Verifica se o filtro por data está ativo
        bool filtrarData = ui->checkDataAgenda->isChecked();

        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();

        // Obtém a data selecionada
        QDate data = ui->calendarioAgenda->selectedDate();

        QString pesquisado = ui->lineEditAgenda->text(); // Pegando o texto do lineEditAgenda

        QSqlQuery query;

        if (!filtrarMinhaAgenda){

            if (filtrarData && pesquisado.isEmpty()) {

                query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data");
                query.bindValue(":data", data.toString("dd/MM/yyyy")); // Ou qualquer formato necessário

            } else if (filtrarData && !pesquisado.isEmpty()){

                // Filtra conforme o texto digitado e a opção selecionada na comboBox
                QString opcaoSelecionada = ui->comboBoxAgenda->currentText(); // Pega a opção selecionada no ComboBox

                if (opcaoSelecionada == "Profissional") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND data = :data");                                                              // ERRO
                    query.bindValue(":profissional", pesquisado + "%");
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));

                } else if (opcaoSelecionada == "Paciente") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND data = :data");                                                                      // ERRO
                    query.bindValue(":paciente", pesquisado + "%");
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));

                } else if (opcaoSelecionada == "Especialidade") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND data = :data");                                                            // ERRO
                    query.bindValue(":especialidade", pesquisado + "%");
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                }
            }
        } else {

            if (filtrarData && pesquisado.isEmpty()) {

                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data");
                query.bindValue(":id_profissional", id_usuario);
                query.bindValue(":data", data.toString("dd/MM/yyyy")); // Ou qualquer formato necessário

            } if (filtrarData && !pesquisado.isEmpty()){

                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE :paciente AND data = :data");
                query.bindValue(":id_profissional", id_usuario);
                query.bindValue(":paciente", pesquisado + "%");
                query.bindValue(":data", data.toString("dd/MM/yyyy"));

            }
        }

        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }

    }

    /////////////////////////////////////////////////////////////////

    // MÉTODO PARA AJUSTAR A TABLE DA AGENDA

    void MainWindow::setAgenda(QSqlQuery &query)
    {
        int tb_linha = 0;

        // Limpa os dados antigos da tabela
        ui->tw_agenda->clearContents();
        ui->tw_agenda->setRowCount(0);  // Reseta as linhas

        ui->tw_agenda->setColumnCount(7);                                                                        // SETA A TABLE EM 7 COLUNAS
        while(query.next()){

            ui->tw_agenda->insertRow(tb_linha);

            for(int i = 0; i <= 6; i++){
                ui->tw_agenda->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));              // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
            }
            ui->tw_agenda->setRowHeight(tb_linha,20);

            tb_linha++;
        }

        QStringList cabecalho = {"ID", "Profissional", "Paciente", "Especialidade", "Data", "Hora", "Status"};
        ui->tw_agenda->setHorizontalHeaderLabels(cabecalho);
        ui->tw_agenda->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_agenda->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_agenda->verticalHeader()->setVisible(false);
        ui->tw_agenda->setStyleSheet("QTableWidget::item:selected {background-color: blue}");

        redimensionarTable(ui->tw_agenda);                                                                          // REDIMENSIONANDO A TABELA
    }


// FIM DA PÁGINA AGENDA


////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "ATENDIMENTO"

void MainWindow::on_btnAtendimento_clicked()
{
    if(logado){
        resetButtonStyles();
        ui->btnAtendimento->setStyleSheet("background-color: rgb(179, 213, 243);");                                       // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnAtendimento->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Atendimento);                                                              // PÁGINA ATENDIMENTO
        ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
    }
}

// FIM DA PÁGINA ATENDIMENTO


/////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "PACIENTES"

void MainWindow::on_btnPacientes_clicked()
{
    if(logado){
        resetButtonStyles();
        ui->btnPacientes->setStyleSheet("background-color: rgb(179, 213, 243);");                                       // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnPacientes->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Pacientes);                                                                // PÁGINA PACIENTES
        ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA

        QSqlQuery query;
        query.prepare("SELECT * FROM tb_pacientes");                                                                    // ACESSANDO A TABELA NO BANCO

        if(query.exec()){
            setTabelaPacientes(query);                                                                                  // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
        }else{
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
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

        QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
        ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
        ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_pacientes->verticalHeader()->setVisible(false);
        ui->tw_pacientes->setStyleSheet("QTableWidget::item:selected {background-color: blue}");

        redimensionarTable(ui->tw_pacientes);                                                                       // REDIMENSIONANDO A TABELA
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
    void MainWindow::adicionarPacienteNaTabela(int id)                                                                 //    <-------
    {
        QSqlQuery query;                                                                                               // ESSE MÉTODO SÓ SERÁ USADO QUANDO A CONEXÃO RETORNAR TRUE, OU SEJA, QUANDO O PACIENTE FOR CADASTRADO
        query.prepare("SELECT * FROM tb_pacientes WHERE id = :id");                                                    // FAZENDO A QUERY SELECT COM O NOVO ID VINDO DAS CONEXÕES

        query.bindValue(":id", id);

        if(query.exec() && query.first()){
            int linha = ui->tw_pacientes->rowCount();
            ui->tw_pacientes->insertRow(linha);                                                                        // ADICIONANDO UMA NOVA LINHA NA TABLE
            for(int i = 0; i <= 8; i++){
                ui->tw_pacientes->setItem(linha, i, new QTableWidgetItem(query.value(i).toString()));                  // ATUALIZANDO A TABLE
                redimensionarTable(ui->tw_pacientes);                                                                  // REDIMENSIONANDO A TABLE
            }
        } else {
            QMessageBox::warning(this, " ", "Erro ao carregar o novo paciente.");
        }
    }
    //
    // MÉTODO DE APAGAR PACIENTE
    //
    void MainWindow::on_btnApagarPac_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_pacientes->currentRow() == -1) {
            QMessageBox::warning(nullptr, " ", "Nenhuma paciente foi selecionado.");                                  // CONFERINDO SE ALGUM PACIENTE FOI SELECIONADO
            return;
        }
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(nullptr,
                                         " ",
                                         "Deseja apagar o paciente ?",                                                    // CONFIRMANDO A AÇÃO DO USUÁRIO
                                         QMessageBox::Ok | QMessageBox::Cancel);

        if (resposta == QMessageBox::Cancel) {
            return;
        } else {
            // Verificando qual é a linha selecionada e descobrindo o id dela
            int linha = ui->tw_pacientes->currentRow();                                                                    // ARMAZENANDO A LINHA SELECIONADA
            QString id = ui->tw_pacientes->item(linha, 0)->text();                                                         // ARMAZENANDO O ID DO PACIENTE SELECIONADO

            // Query para excluir
            QSqlQuery query;
            query.prepare("DELETE FROM tb_pacientes WHERE id="+id);                                                        // DELETANDO O PACIENTE DO BANCO DE DADOS

            if(query.exec()){
                // Removendo a linha do Table
                ui->tw_pacientes->removeRow(linha);
                QMessageBox::information(this," ","Excluído");                                                              // REMOVENDO LINHA DA TABLE E GERANDO O POP-UP
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir registro");
            }
        }
    }

    //
    // MÉTODO DE EDITAR PACIENTE
    //
    void MainWindow::on_btnEditarPac_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_pacientes->currentRow() == -1) {
            QMessageBox::warning(nullptr, " ", "Nenhuma paciente foi selecionado.");                                // CONFERINDO SE ALGUM PACIENTE FOI SELECIONADO
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
            redimensionarTable(ui->tw_pacientes);                                                                       // AJUSTAR TABLE
        }else{
            QMessageBox::warning(this, " ", "Erro ao atualizar paciente na tabela");
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
            QMessageBox::warning(this, " ", "Não foi possível acessar os pacientes no banco de dados");
        }
    }

// FIM PÁGINA PACIENTES


//////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "COLABORADORES"

void MainWindow::on_btnColaboradores_clicked()
{
    if(logado){
        resetButtonStyles();
        ui->btnColaboradores->setStyleSheet("background-color: rgb(179, 213, 243);");                                   // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnColaboradores->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Colaboradores);                                                            // PÁGINA COLABORADORES
        ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA

        QSqlQuery query;
        query.prepare("SELECT * FROM tb_colaboradores");                                                                // ACESSANDO A TABELA NO BANCO

        if(query.exec()){
            setTabelaColaboradores(query);                                                                              // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
        }else{
            qDebug() << "Erro ao acessar o banco de dados";
        }
    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
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

        QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Cargo", "NºCelular", "E-mail", "Nascimento"};
        ui->tw_colaboradores->setHorizontalHeaderLabels(cabecalho);
        ui->tw_colaboradores->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_colaboradores->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_colaboradores->verticalHeader()->setVisible(false);
        ui->tw_colaboradores->setStyleSheet("QTableWidget::item:selected {background-color: blue}");

        redimensionarTable(ui->tw_colaboradores);                                                                   // REDIMENSIONANDO A TABELA
    }

    void MainWindow::on_btnCadastroCol_clicked()
    {
        cadastroColaboradores cadastramento(this);                                                                     // CRIANDO A JANELA DE CADASTRO

        // O SINAL QUE TRAZ O ID DO COLABORADOR CADASTRADO PARA JANELA
        bool connected = connect(&cadastramento, &cadastroColaboradores::colaboradorCadastrado,                        // PRINCIPAL É EMITIDO PELO OBJETO COLABORADOR, QUE É O ÚNICO QUE
                                 this, &MainWindow::adicionarColaboradorNaTabela);                                     // TEM ACESSO DIRETO A QUERY DE INSERT, PARA A JANELA DE
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
                redimensionarTable(ui->tw_colaboradores);                                                              // REDIMENSIONANDO A TABLE
            }
        } else {
            QMessageBox::warning(this, " ", "Erro ao carregar o novo colaborador.");
        }
    }
    //
    // MÉTODO DE APAGAR COLABORADOR
    //
    void MainWindow::on_btnApagarCol_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_colaboradores->currentRow() == -1) {
            QMessageBox::warning(nullptr, " ", "Nenhuma colaborador foi selecionado.");                                     // CONFERINDO SE ALGUM COLABORADOR  FOI SELECIONADO
            return;
        }
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(nullptr,
                                         " ",
                                         "Deseja apagar o colaborador ?",                                                   // CONFIRMANDO A AÇÃO DO USUÁRIO
                                         QMessageBox::Ok | QMessageBox::Cancel);

        if (resposta == QMessageBox::Cancel) {
            return;
        } else {
            // Verificando qual é a linha selecionada e descobrindo o id dela
            int linha = ui->tw_colaboradores->currentRow();                                                                 // ARMAZENANDO A LINHA SELECIONADA
            QString id = ui->tw_colaboradores->item(linha, 0)->text();                                                      // ARMAZENANDO O ID DO COLABORADOR  SELECIONADO

            // Query para excluir
            QSqlQuery query;
            query.prepare("DELETE FROM tb_colaboradores WHERE id="+id);                                                     // DELETANDO O COLABORADOR DO BANCO DE DADOS

            if(query.exec()){
                // Removendo a linha do Table
                ui->tw_colaboradores->removeRow(linha);
                QMessageBox::information(this," ","Excluído");                                                               // REMOVENDO LINHA DA TABLE E GERANDO O POP-UP
            }else{
                QMessageBox::warning(this, " ", "Erro ao excluir registro");
            }
        }
    }
    //
    // MÉTODO DE EDITAR COLABORADOR
    //
    void MainWindow::on_btnEditarCol_clicked()
    {
        // Conferindo se o usuário selecionou alguma linha (currentRow() retorna -1 quando não há linha selecionada)
        if (ui->tw_colaboradores->currentRow() == -1) {
            QMessageBox::warning(nullptr, " ", "Nenhuma colaborador foi selecionado.");                             // CONFERINDO SE ALGUM COLABORADOR FOI SELECIONADO
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
            redimensionarTable(ui->tw_colaboradores);                                                                   // AJUSTAR TABLE
        }else{
            QMessageBox::warning(this, " ", "Erro ao atualizar colaborador na tabela");
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
            QMessageBox::warning(this, " ", "Não foi possível acessar os colaboradores no banco de dados");
        }
    }


// FIM PÁGINA COLABORADORES


//////////////////////////////////////////////////



// MÉTODO PARA ACESSAR A PÁGINA "RELATÓRIOS"

void MainWindow::on_btnRelatorios_clicked()
{
    if(logado){
        resetButtonStyles();
        ui->btnRelatorios->setStyleSheet("background-color: rgb(179, 213, 243);");                                      // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnRelatorios->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Relatorios);                                                               // PÁGINA RELATÓRIOS
        ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
    }
}

// FIM DA PÁGINA RELATÓRIOS


////////////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "FORNECEDORES"

void MainWindow::on_btnFornecedores_clicked()
{
    if(logado){
        resetButtonStyles();
        ui->btnFornecedores->setStyleSheet("background-color: rgb(179, 213, 243);");                                    // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnFornecedores->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Fornecedores);                                                             // PÁGINA FORNECEDORES
        ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
    }
}

// FIM DA PÁGINA FORNCEDORES


///////////////////////////////////////////////////

