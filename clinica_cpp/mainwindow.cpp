#include "mainwindow.h"
#include "./ui_mainwindow.h"

// DEFINIÇÃO DA JANELA PRINCIPAL, QUE INCLUEM AS TABLEWIDGETS E SEUS BOTÕES

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                                                                                              // CONSTRUTOR

}


//////////////////////////////////////////



MainWindow::~MainWindow()
{
    delete ui;                                                                                                      // DESTRUTOR
}


//////////////////////////////////////////


// MÉTODOS GET E SET PARA ACESO DE DADOS PRIVADOS

bool MainWindow::getLogado() const
{
    return logado;
}

QString MainWindow::getNomeUsuario() const
{
    return nome_usuario;
}

QString MainWindow::getClinica() const
{
    return clinica_usuario;
}

QString MainWindow::getCargo() const
{
    return cargo_usuario;
}

int MainWindow::getIdUsuario() const
{
    return id_usuario;
}

int MainWindow::getIdSessao() const
{
    return idSessaoSelecionada;
}

/////////////////////////////////////////

void MainWindow::setLogado(bool login)
{
    logado = login;
}

void MainWindow::setNomeUsuario(QString nome)
{
    nome_usuario = nome;
}

void MainWindow::setClinica(QString clin)
{
    clinica_usuario = clin;
}

void MainWindow::setCargo(QString carg)
{
    cargo_usuario = carg;
}

void MainWindow::setIdUsuario(int Id)
{
    id_usuario = Id;
}

void MainWindow::setIdSessao(int Id)
{
    idSessaoSelecionada = Id;
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
    palette.setColor(QPalette::PlaceholderText, QColor(127, 127, 127));
    palette.setColor(QPalette::Button, QColor(240, 240, 240));          // Cor de fundo do botão
    palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));            // Cor do texto do botão
    palette.setColor(QPalette::BrightText, QColor(255, 0, 0));

    app.setPalette(palette);                                            // Setando a peleta no app
}

///////////////////////////////////////////

// MÉTODO PARA ABRIR O PDF DE INSTRUÇÕES DE USUÁRIO

void MainWindow::abrirPdf(const QString &link) {
    // Caminho temporário para salvar o PDF
    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/guide.pdf";

    // Copia o arquivo PDF do recurso para o caminho temporário
    QFile::copy(":/extraFiles/guide.pdf", tempPath);

    // Abre o arquivo PDF
    QDesktopServices::openUrl(QUrl::fromLocalFile(tempPath));
}

//////////////////////////////////////////


// MÉTODO PARA FORMATAR A PÁGINA PRINCIPAL E DEFINIR A PÁGINA DE INÍCIO

void MainWindow::janelaFormatada(){

    setWindowTitle("MEDICALSOFT");                                                                                  // TÍTULO DA JANELA

    ui->paginas->tabBar()->setVisible(false);                                                                       // DEIXANDO OS ÍCONES DAS PÁGINAS DA TABWIDGET INVISÍVEIS

    ui->tab_relatorios->tabBar()->setVisible(false);                                                                // MESMA COISA AQUI PARA A OUTRA TABWIDGET

    QPixmap logo(":/icons/logo.png");
    ui->logo->setPixmap(logo.scaled(105, 105, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->labelPdf->setText("<a href=\"guide.pdf\">Instruções de uso</a>");
    ui->labelPdf->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->labelPdf->setOpenExternalLinks(false);  // Para capturar o clique no link

    // Conecte o sinal linkActivated ao slot
    connect(ui->labelPdf, &QLabel::linkActivated, this, &MainWindow::abrirPdf);

    QPixmap img(":/extraFiles/imgInicial.jpg");
    ui->imgInicial->setPixmap(img.scaled(500, 750, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // FORMATANDO O LAYOUT SUPERIOR

    // Adicionando efeito de sombra ao frame superior
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);  // Aumentando o desfoque para 15px
    shadowEffect->setOffset(0, 7);  // Deslocando a sombra 10px para baixo
    shadowEffect->setColor(QColor(0, 0, 0, 150));  // Definindo cor da sombra com maior opacidade

    ui->frameSuperior->setGraphicsEffect(shadowEffect);

    //COLOCANDO O LAYOUT LATERAL ABAIXO PARA APLICAR O EFEITO DE SOMBRA

    ui->frameSuperior->raise(); // Traz o framesuperior para frente
    ui->frameLateral->lower(); // Envia o framelateral para trás

    /////////////////////////////////////////////////

    // Estilizando o calendário
    ui->calendarioAgenda->setStyleSheet(
        "QCalendarWidget QWidget#qt_calendar_navigationbar {"
        "    background-color: #dcdcdc;"  // Cor de fundo da barra de navegação
        "}"
        "QCalendarWidget QToolButton {"
        "    color: #000000;"  // Cor do texto dos botões
        "}"
        "QCalendarWidget QAbstractItemView:enabled {"
        "    selection-background-color: #a0c4ff;"  // Cor de fundo da seleção
        "    selection-color: #000000;"  // Cor do texto da seleção
        "}"
        );

    // Alterar o ícone das setas de navegação
    QToolButton *prevMonthButton = ui->calendarioAgenda->findChild<QToolButton *>("qt_calendar_prevmonth");
    QToolButton *nextMonthButton = ui->calendarioAgenda->findChild<QToolButton *>("qt_calendar_nextmonth");

    prevMonthButton->setIcon(QIcon(":/icons/prev.png"));  // Substitua pelo caminho do seu ícone
    nextMonthButton->setIcon(QIcon(":/icons/next.png"));  // Substitua pelo caminho do seu ícone

    ///////////////////////////////////////////////////

    setLogado(false);

    on_btnInicio_clicked();                                                 // DEFINI A PÁGINA INICIAL COMO SEMPRE A PRIMEIRA AO ABRIR O PROGRAMA
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

// MÉTODOS PARA O ESTILO DOS BOTÕES

void MainWindow::resetButtonStyles() {
    QList<QPushButton*> botoes = {
        ui->btnAgenda, ui->btnAtendimento, ui->btnPacientes,
        ui->btnColaboradores, ui->btnEstoque, ui->btnRelatorios, ui->btnInicio
    };

    for (auto botao : botoes) {
        botao->setStyleSheet("");
    }
}

void MainWindow::setButtonHighlight(QPushButton *botao)
{
    if (botaoAtivo != botao) {
        resetButtonStyles();
        botao->setStyleSheet("background-color: rgb(179, 213, 243);");                                            // APLICANDO UM HIGHLIGHT COM CSS
        botaoAtivo = botao;
    }
}

void MainWindow::setLayoutEntrar()
{
    ui->btnEntrar->setText("Entrar");
    ui->btnEntrar->setStyleSheet(
        "QPushButton {"
        "    background-color: #6db0ec; "
        "    color: #000000; "                                                                                   // TRANSFORMANDO O BOTÃO EM LOGIN
        "    border: 2px solid #dcdcdc; "
        "    border-radius: 10px; "
        "}"
        "QPushButton:hover {"
        "    background-color: #dcdcdc;"  // Cor de fundo ao passar o mouse
        "}"
        );

    ui->iconPerfil->clear();
    ui->txtUsuario->clear();
    ui->txtClinica->clear();
    ui->txtCargo->clear();

    // Atualiza outras partes da interface
    ui->tw_pacientes->setRowCount(0);
    ui->tw_pacientes->setColumnCount(0);
    ui->tw_colaboradores->setRowCount(0);
    ui->tw_colaboradores->setColumnCount(0);

    // Volta para a página inicial
    on_btnInicio_clicked();
}

void MainWindow::setLayoutSair()
{
    ui->btnEntrar->setText("Sair");
    ui->btnEntrar->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(200, 20, 20); "
        "    color: #ffffff; "                                                                                    // TRANFORMANDO O BOTÃO EM LOGOUT
        "    border-radius: 10px; "
        "}"
        "QPushButton:hover {"
        "    background-color: darkred;"  // Cor de fundo ao passar o mouse
        "}"
        );

    QPixmap icone(":/icons/Generic avatar.png");
    ui->iconPerfil->setPixmap(icone.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->txtUsuario->setText(getNomeUsuario());

    ui->txtUsuario->setStyleSheet(
        "QLabel {"
        "    font-family: 'Poppins', sans-serif;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "    color: #000000;"  // Azul mais escuro
        "    letter-spacing: 1px;"
        "    text-transform: uppercase;"
        "}"
        );

    ui->txtCargo->setText(" - " +cargo_usuario);

    ui->txtCargo->setStyleSheet(
        "QLabel {"
        "    font-family: 'Poppins', sans-serif;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "    color: #000000;"  // Azul mais escuro
        "    letter-spacing: 1px;"
        "    text-transform: uppercase;"
        "}"
        );

    ui->txtClinica->setText(clinica_usuario);

    ui->txtClinica->setStyleSheet(
        "QLabel {"
        "    font-family: 'Poppins', sans-serif;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "    color: #000000;"  // Azul mais escuro
        "    letter-spacing: 1px;"
        "    text-transform: uppercase;"
        "}"
        );
}

//////////////////////////////////////////

// MÉTODO PARA ATUALIZAR O SISTEMA QUANDO O USUÁRIO LOGAR

void MainWindow::usuarioEntrou(){

    setLogado(true);                                                                                              // ESTADO DE LOGIN TRUE

    setLayoutSair();

}

/////////////////////////////////////////

// MÉTODO PARA ATUALIZAR O SISTEMA QUANDO O USUÁRIO DESLOGAR

void MainWindow::usuarioSaiu(){

    setLogado(false);                                                                                               // ESTADO DE LOGIN FALSE
    conexao.fechar();                                                                                               // FECHANDO CONEXÃO COM O BANCO

    setLayoutEntrar();
}


//////////////////////////////////////////

// MÉTODO PARA ACESSAR A JANELA "ENTRAR"

void MainWindow::on_btnEntrar_clicked() {
    if (!getLogado()) {                                                                                                   // NÃO LOGADO, LOGANDO
        janela_entrar janelaEntrar(this, &conexao);                                                                  // Passando a conexão para a janela de login
        janelaEntrar.exec();

        if (janelaEntrar.getLogadoJanela()) {                                                                             // Verifica se o login foi bem-sucedido

            // Atualiza informações do usuário usando os dados emitidos pela janela_entrar
            setIdUsuario(janelaEntrar.getId());
            setNomeUsuario(janelaEntrar.getNome());
            setClinica(janelaEntrar.getClinica());
            setCargo(janelaEntrar.getCargo());

            usuarioEntrou();
        } else {
            conexao.fechar();
        }

    } else {                                                                                                        // LOGADO, SAINDO
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, " ", "Tem certeza que deseja sair de sua conta?", QMessageBox::Yes | QMessageBox::No);

        if (resposta == QMessageBox::Yes) {
            usuarioSaiu();
        }
    }
}


/////////////////////////////////////////

// MÉTODO PARA ACESSAR A PÁGINA "INICIO"

void MainWindow::on_btnInicio_clicked()
{
    setButtonHighlight(ui->btnInicio);                                                                              // ALTERAR A COR DE DESTAQUE DO BOTÃO
    ui->btnInicio->setAutoFillBackground(true);

    int index = ui->paginas->indexOf(ui->Inicio);                                                                   // PÁGINA INICIO
    ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA
}

// FIM DA PÁGINA INICIO


///////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "AGENDA"

void MainWindow::on_btnAgenda_clicked()
{
    if(getLogado()){
        setButtonHighlight(ui->btnAgenda);                                                                              // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnAgenda->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Agenda);                                                                     // PÁGINA AGENDA
        ui->paginas->setCurrentIndex(index);

        QSqlQuery query;

        QDate data = ui->calendarioAgenda->selectedDate();

        ui->checkDataAgenda->setChecked(true);
        ui->checkMinhaAgenda->setChecked(true);
        ui->comboBoxStatusAgenda->setCurrentIndex(0);

        query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
                      "AND data = :data and status_sessao = :status ORDER BY data ASC, hora ASC");                          // ACESSANDO A TABELA NO BANCO

        query.bindValue(":id_profissional", getIdUsuario());
        query.bindValue(":data", data.toString("dd/MM/yyyy"));
        query.bindValue(":status", "Aguardando");

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

////////////////////////////////////////////////////////////////


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
            ui->tw_agenda->setRowHeight(tb_linha,30);

            tb_linha++;
        }

        QStringList cabecalho = {"ID", "Profissional", "Paciente", "Especialidade", "Data", "Hora", "Status"};
        ui->tw_agenda->setHorizontalHeaderLabels(cabecalho);
        ui->tw_agenda->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_agenda->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_agenda->verticalHeader()->setVisible(false);

        // Estilizando a tabela com CSS
        ui->tw_agenda->setStyleSheet(
            "QTableWidget {"
            "    border: 3px solid #dcdcdc;"
            "    border-radius: 10px;"
            "    background-color: #ffffff;"
            "    gridline-color: #dcdcdc;"
            "}"
            "QHeaderView::section {"
            "    background-color: #f0f0f0;"
            "    border: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "    border-radius: 5px;"
            "}"
            "QTableWidget::item {"
            "    border-bottom: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "}"
            "QTableWidget::item:selected {"
            "    background-color: #a0c4ff;"
            "    color: #000000;"
            "}"
        );

        redimensionarTable(ui->tw_agenda);                                                                          // REDIMENSIONANDO A TABELA
    }

    ////////////////////////////////////////////////////////////////

    // MÉTODO DE PESQUISA

    void MainWindow::on_checkDataAgenda_checkStateChanged(const Qt::CheckState &arg1)
    {
        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();
        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo
        QString statusSelecionado = ui->comboBoxStatusAgenda->currentText(); // Opção do comboBoxStatusAgenda
        QDate data = ui->calendarioAgenda->selectedDate();
        QSqlQuery query;

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (filtrarMinhaAgenda) {
            ui->lineEditAgenda->clear();
            ui->comboBoxAgenda->setEnabled(false);

            if (!filtrarData) {
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
                              "AND status_sessao = :status ORDER BY data ASC, hora ASC");

                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":status", statusSelecionado);
            } else {
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
                              "AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");

                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            }
        } else {
            ui->comboBoxAgenda->setEnabled(true);

            if (!filtrarData) {
                query.prepare("SELECT * FROM tb_agendamentos WHERE status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":status", statusSelecionado);
            } else {
                query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            }
        }

        // Executa a query
        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }


    void MainWindow::on_checkMinhaAgenda_stateChanged(int arg1)
    {
        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();
        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo
        QString statusSelecionado = ui->comboBoxStatusAgenda->currentText(); // Opção do comboBoxStatusAgenda
        QDate data = ui->calendarioAgenda->selectedDate();
        QSqlQuery query;

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (filtrarMinhaAgenda) {
            ui->lineEditAgenda->clear();
            ui->comboBoxAgenda->setCurrentIndex(0);
            ui->comboBoxAgenda->setEnabled(false);

            if (!filtrarData) {
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":status", statusSelecionado);
            } else {
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            }
        } else {
            ui->comboBoxAgenda->setEnabled(true);

            if (!filtrarData) {
                query.prepare("SELECT * FROM tb_agendamentos WHERE status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":status", statusSelecionado);
            } else {
                query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
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

        QString pesquisado = ui->lineEditAgenda->text(); // Pegando o texto do lineEditAgenda
        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo
        QString opcaoSelecionada = ui->comboBoxAgenda->currentText(); // Opção do comboBox
        QString statusSelecionado = ui->comboBoxStatusAgenda->currentText(); // Opção do comboBoxStatusAgenda
        QDate data = ui->calendarioAgenda->selectedDate(); // Data selecionada no calendário
        QSqlQuery query;

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (filtrarData) {
            // Filtro por data ativado
            if (pesquisado.isEmpty()) {
                query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            } else {
                if (opcaoSelecionada == "Profissional") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":profissional", pesquisado + "%");
                } else if (opcaoSelecionada == "Paciente") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":paciente", pesquisado + "%");
                } else if (opcaoSelecionada == "Especialidade") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":especialidade", pesquisado + "%");
                }
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            }
        } else {
            // Filtro por data desativado
            if (pesquisado.isEmpty()) {
                query.prepare("SELECT * FROM tb_agendamentos WHERE status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":status", statusSelecionado);
            } else {
                if (opcaoSelecionada == "Profissional") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":profissional", pesquisado + "%");
                } else if (opcaoSelecionada == "Paciente") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":paciente", pesquisado + "%");
                } else if (opcaoSelecionada == "Especialidade") {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":especialidade", pesquisado + "%");
                }
                query.bindValue(":status", statusSelecionado);
            }
        }
        // Executa a query
        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }


    void MainWindow::on_comboBoxStatusAgenda_currentTextChanged(const QString &arg1)
    {
        ui->lineEditAgenda->clear();

        QString statusSelecionado = ui->comboBoxStatusAgenda->currentText(); // Opção do comboBoxStatusAgenda
        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo
        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked(); // Verifica se o filtro "Minha Agenda" está ativo
        QDate data = ui->calendarioAgenda->selectedDate(); // Data selecionada no calendário
        QSqlQuery query;

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (filtrarMinhaAgenda) {
            // Lógica para quando "Minha Agenda" está ativado
            if (filtrarData) {
                // Filtrar pela data, pela agenda do usuário e pelo status
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            } else {
                // Filtrar pela agenda do usuário e pelo status
                query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":status", statusSelecionado);
            }
        } else {
            // Lógica para quando "Minha Agenda" não está ativado
            if (filtrarData) {
                // Filtrar pela data e pelo status
                query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status", statusSelecionado);
            } else {
                // Filtrar apenas pelo status
                query.prepare("SELECT * FROM tb_agendamentos WHERE status_sessao = :status ORDER BY data ASC, hora ASC");
                query.bindValue(":status", statusSelecionado);
            }
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
        QString opcaoSelecionada = ui->comboBoxAgenda->currentText(); // Opção do comboBox
        QString statusSelecionado = ui->comboBoxStatusAgenda->currentText(); // Opção do comboBoxStatusAgenda
        QDate data = ui->calendarioAgenda->selectedDate(); // Data selecionada no calendário
        QSqlQuery query;

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (!filtrarMinhaAgenda) {
            if (filtrarData) {
                // Filtro por data ativado
                if (pesquisado.isEmpty()) {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                } else {
                    if (opcaoSelecionada == "Profissional") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":profissional", pesquisado + "%");
                    } else if (opcaoSelecionada == "Paciente") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":paciente", pesquisado + "%");
                    } else if (opcaoSelecionada == "Especialidade") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":especialidade", pesquisado + "%");
                    }
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                }
            } else {
                // Filtro por data desativado
                if (pesquisado.isEmpty()) {
                    query.prepare("SELECT * FROM tb_agendamentos WHERE status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":status", statusSelecionado);
                } else {
                    if (opcaoSelecionada == "Profissional") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":profissional", pesquisado + "%");
                    } else if (opcaoSelecionada == "Paciente") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":paciente", pesquisado + "%");
                    } else if (opcaoSelecionada == "Especialidade") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":especialidade", pesquisado + "%");
                    }
                    query.bindValue(":status", statusSelecionado);
                }
            }
        } else {
            // Lógica para quando "Minha Agenda" está ativado
            if (filtrarData) {
                if (pesquisado.isEmpty()) {
                    // Filtrar apenas pela data e pela agenda do usuário
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                } else {
                    // Filtrar pela data, pela agenda do usuário e pelo texto digitado
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE :paciente AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":paciente", pesquisado + "%");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                }
            } else {
                if (pesquisado.isEmpty()) {
                    // Filtrar apenas pela agenda do usuário
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":status", statusSelecionado);
                } else {
                    // Filtrar pela agenda do usuário e pelo texto digitado somente de pacientes porque so posso filtrar pacientes na minha agenda
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE :paciente AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":paciente", pesquisado + "%");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":status", statusSelecionado);
                }
            }
        }

        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela
        } else {
            qDebug() << "Erro ao executar a query O ERRO ESTÁ AQUI:" << query.lastError().text();
        }
    }


    void MainWindow::on_calendarioAgenda_clicked(const QDate &date)
    {
        // Mantém a data selecionada visualmente
        ui->calendarioAgenda->setSelectedDate(date);

        atualizarTabelaPorData();
    }

    void MainWindow::atualizarTabelaPorData()
    {
        QDate data = ui->calendarioAgenda->selectedDate(); // Obtém a data selecionada
        bool filtrarData = ui->checkDataAgenda->isChecked(); // Verifica se o filtro por data está ativo
        bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked(); // Verifica se o filtro "minha agenda" está ativo
        QString pesquisado = ui->lineEditAgenda->text(); // Texto digitado na lineEdit
        QString opcaoSelecionada = ui->comboBoxAgenda->currentText(); // Opção selecionada no comboBox
        QString statusSelecionado = ui->comboBoxStatusAgenda->currentText(); // Opção do comboBoxStatusAgenda
        QSqlQuery query;

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (!filtrarMinhaAgenda) {
            // Lógica para quando "Minha Agenda" não está ativado
            if (filtrarData) {
                if (pesquisado.isEmpty()) {
                    // Filtrar apenas pela data
                    query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                } else {
                    // Filtrar pela data e pelo texto digitado
                    if (opcaoSelecionada == "Profissional") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":profissional", pesquisado + "%");
                    } else if (opcaoSelecionada == "Paciente") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":paciente", pesquisado + "%");
                    } else if (opcaoSelecionada == "Especialidade") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":especialidade", pesquisado + "%");
                    }
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                }
            } else {
                // Filtro por data desativado
                if (pesquisado.isEmpty()) {
                    // Sem filtros (tudo)
                    query.prepare("SELECT * FROM tb_agendamentos WHERE status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":status", statusSelecionado);
                } else {
                    // Filtrar apenas pelo texto digitado
                    if (opcaoSelecionada == "Profissional") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE profissional LIKE :profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":profissional", pesquisado + "%");
                    } else if (opcaoSelecionada == "Paciente") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE paciente LIKE :paciente AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":paciente", pesquisado + "%");
                    } else if (opcaoSelecionada == "Especialidade") {
                        query.prepare("SELECT * FROM tb_agendamentos WHERE especialidade LIKE :especialidade AND status_sessao = :status ORDER BY data ASC, hora ASC");
                        query.bindValue(":especialidade", pesquisado + "%");
                    }
                    query.bindValue(":status", statusSelecionado);
                }
            }
        } else {
            // Lógica para quando "Minha Agenda" está ativado
            if (filtrarData) {
                if (pesquisado.isEmpty()) {
                    // Filtrar apenas pela data e pela agenda do usuário
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                } else {
                    // Filtrar pela data, pela agenda do usuário e pelo texto digitado
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE :paciente AND data = :data AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":paciente", pesquisado + "%");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":data", data.toString("dd/MM/yyyy"));
                    query.bindValue(":status", statusSelecionado);
                }
            } else {
                if (pesquisado.isEmpty()) {
                    // Filtrar apenas pela agenda do usuário
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":status", statusSelecionado);
                } else {
                    // Filtrar pela agenda do usuário e pelo texto digitado somente de pacientes porque so posso filtrar pacientes na minha agenda
                    query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE :paciente AND status_sessao = :status ORDER BY data ASC, hora ASC");
                    query.bindValue(":paciente", pesquisado + "%");
                    query.bindValue(":id_profissional", getIdUsuario());
                    query.bindValue(":status", statusSelecionado);
                }
            }
        }

        // Executa a consulta
        if (query.exec()) {
            setAgenda(query); // Atualiza a tabela com os resultados
        } else {
            qDebug() << "Erro ao executar a query DE DATA:" << query.lastError().text();
        }
    }


    /////////////////////////////////////////////////////////////////

    // MÉTODOS DE CADASTRO DE SESSÃO

    void MainWindow::on_btnAgendar_clicked()
    {
        cadastroSessao *cadastrarSessao = new cadastroSessao(this, "Cadastrar");

        // Conectando o sinal ao slot que adiciona a sessão na tabela
        bool connected = connect(cadastrarSessao, &cadastroSessao::sessaoCadastrada,
                                 this, &MainWindow::adicionarSessaoNaTabela);

        if (!connected) {
            qDebug() << "Erro ao conectar o sinal sessaoCadastrada";
        }

        cadastrarSessao->show();
    }

    void MainWindow::adicionarSessaoNaTabela(int idSessao)
    {
        carregarTabelaAgendamentos();
    }

    void MainWindow::carregarTabelaAgendamentos()
    {
        ui->tw_agenda->setRowCount(0);  // Limpa a tabela antes de carregar os dados

        QSqlQuery query;
        if (ui->checkDataAgenda->isChecked()) {
            query.prepare("SELECT * FROM tb_agendamentos WHERE data = :data ORDER BY data ASC, hora ASC");
            query.bindValue(":data", ui->calendarioAgenda->selectedDate().toString("dd/MM/yyyy"));
        } else {
            query.prepare("SELECT * FROM tb_agendamentos ORDER BY data ASC, hora ASC");
        }

        if (query.exec()) {
            while (query.next()) {
                int linha = ui->tw_agenda->rowCount();
                ui->tw_agenda->insertRow(linha);

                for (int i = 0; i < query.record().count(); ++i) {
                    QVariant value = query.value(i);
                    ui->tw_agenda->setItem(linha, i, new QTableWidgetItem(value.toString()));
                }
            }
            redimensionarTable(ui->tw_agenda);
        } else {
            QMessageBox::warning(this, " ", "Erro ao carregar os agendamentos.");
        }
    }

    // MÉTODOS DE EDIÇÃO DE SESSÃO

    void MainWindow::on_tw_agenda_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
    {
        if (currentRow >= 0 && ui->tw_agenda->item(currentRow, 0)) {
            QString idStr = ui->tw_agenda->item(currentRow, 0)->text();
            setIdSessao(idStr.toInt());  // Convertendo para inteiro
        } else {
            setIdSessao();  // Define o valor inválido -1 caso nenhuma linha esteja selecionada ou a célula esteja vazia
        }
    }

    void MainWindow::on_btnEditarAgenda_clicked()
    {
        int linha = ui->tw_agenda->currentRow();

        if (getIdSessao() != -1 && linha >= 0) {
            cadastroSessao *cadastrarSessao = new cadastroSessao(this, "Editar", getIdSessao());

            // Conectar o sinal de edição ao slot de atualização
            connect(cadastrarSessao, &cadastroSessao::sessaoEditada,
                    this, &MainWindow::atualizarSessaoNaTabela);

            cadastrarSessao->show();
        } else {
            QMessageBox::warning(this, " ", "Selecione uma sessão para editar.");
        }
    }

    void MainWindow::atualizarSessaoNaTabela(int idSessao)
    {
        carregarTabelaAgendamentos();
    }

    // MÉTODO PARA ENVIAR PARA O RELATÓRIO DE ATENDIMENTO ARMAZENADO DAQUELA SESSÃO

    void MainWindow::on_btnVerRelatorio_clicked()
    {
        int linhaSelecionada = ui->tw_agenda->currentRow();
        if (linhaSelecionada < 0) {
            QMessageBox::warning(this, "Aviso", "Selecione uma sessão para ver o relatório.");
            return;
        }

        QString statusSessao = ui->tw_agenda->item(linhaSelecionada, 6)->text();
        if (statusSessao != "Realizada") {
            QMessageBox::warning(this, "Aviso", "A sessão selecionada ainda não foi realizada.");
            return;
        }

        int idSessao = ui->tw_agenda->item(linhaSelecionada, 0)->text().toInt();

        ui->txtRelAtendimento->clear();

        carregarRelatorios(&idSessao);

        ui->paginas->setCurrentWidget(ui->Relatorios);
        ui->tab_relatorios->setCurrentWidget(ui->Atendimentos);
        resetButtonStyles();
        ui->btnRelatorios->setStyleSheet("background-color: rgb(179, 213, 243);");
        ui->btnRelatorios->setAutoFillBackground(true);
    }



// FIM DA PÁGINA AGENDA


////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "ATENDIMENTO" (OBS MUDAMOS O NOME DA PÁGINA PARA ATENDER)

    void MainWindow::on_btnAtendimento_clicked()
    {
        if (getLogado()) {
            setButtonHighlight(ui->btnAtendimento); // ALTERAR A COR DE DESTAQUE DO BOTÃO
            ui->btnAtendimento->setAutoFillBackground(true);

            ui->checkHoje->setChecked(true);

            int index = ui->paginas->indexOf(ui->Atendimento); // PÁGINA AGENDA
            ui->paginas->setCurrentIndex(index);

            atualizarTabelaAtendimento(); // Atualiza a tabela com filtros e ordenação
        } else {
            QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
        }

        ui->textEdit->clear();
    }

    void MainWindow::setTabelaAtendimento(QSqlQuery &query)
    {
        int tb_linha = 0;

        // Limpa os dados antigos da tabela
        ui->tw_atendimento->clearContents();
        ui->tw_atendimento->setRowCount(0); // Reseta as linhas

        ui->tw_atendimento->setColumnCount(7); // SETA A TABLE EM 7 COLUNAS
        while (query.next()) {
            ui->tw_atendimento->insertRow(tb_linha);

            for (int i = 0; i <= 6; i++) {
                ui->tw_atendimento->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString())); // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
            }
            ui->tw_atendimento->setRowHeight(tb_linha, 30);

            tb_linha++;
        }

        QStringList cabecalho = {"ID", "Profissional", "Paciente", "Especialidade", "Data", "Hora", "Status"};
        ui->tw_atendimento->setHorizontalHeaderLabels(cabecalho);
        ui->tw_atendimento->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_atendimento->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_atendimento->verticalHeader()->setVisible(false);

        // Estilizando a tabela com CSS
        ui->tw_atendimento->setStyleSheet(
            "QTableWidget {"
            "    border: 3px solid #dcdcdc;"
            "    border-radius: 10px;"
            "    background-color: #ffffff;"
            "    gridline-color: #dcdcdc;"
            "}"
            "QHeaderView::section {"
            "    background-color: #f0f0f0;"
            "    border: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "    border-radius: 5px;"
            "}"
            "QTableWidget::item {"
            "    border-bottom: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "}"
            "QTableWidget::item:selected {"
            "    background-color: #a0c4ff;"
            "    color: #000000;"
            "}"
        );

        redimensionarTable(ui->tw_atendimento); // REDIMENSIONANDO A TABELA
    }

    void MainWindow::atualizarTabelaAtendimento()
    {
        QString pesquisado = ui->lineEditAtendimento->text();
        bool filtrarHoje = ui->checkHoje->isChecked();
        QDate data = QDate::currentDate();
        QSqlQuery query;

        // Obter o status selecionado no comboBox
        QString statusSelecionado = ui->comboBoxAtender->currentText();

        if (statusSelecionado == "Paciente ausente"){
            statusSelecionado = "Ausente";
        }

        if (pesquisado.isEmpty()) {
            if (!filtrarHoje) {
                query.prepare(
                    "SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND status_sessao = :status_sessao "
                    "ORDER BY data ASC, hora ASC"
                    );
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":status_sessao", statusSelecionado);
            } else {
                query.prepare(
                    "SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data AND status_sessao = :status_sessao "
                    "ORDER BY data ASC, hora ASC"
                    );
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":status_sessao", statusSelecionado);
            }
        } else {
            if (!filtrarHoje) {
                query.prepare(
                    "SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND paciente LIKE :paciente AND status_sessao = :status_sessao "
                    "ORDER BY data ASC, hora ASC"
                    );
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":paciente", pesquisado + "%");
                query.bindValue(":status_sessao", statusSelecionado);
            } else {
                query.prepare(
                    "SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional AND data = :data AND paciente LIKE :paciente AND status_sessao = :status_sessao "
                    "ORDER BY data ASC, hora ASC"
                    );
                query.bindValue(":id_profissional", getIdUsuario());
                query.bindValue(":data", data.toString("dd/MM/yyyy"));
                query.bindValue(":paciente", pesquisado + "%");
                query.bindValue(":status_sessao", statusSelecionado);
            }
        }

        // Executa a query
        if (query.exec()) {
            setTabelaAtendimento(query); // Atualiza a tabela com os dados ordenados
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }

    void MainWindow::on_comboBoxAtender_currentIndexChanged(int index)
    {
        // Limpa o campo de pesquisa
        ui->lineEditAtendimento->clear();

        // Atualiza a tabela com base no estado atual dos filtros
        atualizarTabelaAtendimento();
    }

    void MainWindow::on_lineEditAtendimento_textChanged(const QString &arg1)
    {
        // Atualiza a tabela com a pesquisa
        atualizarTabelaAtendimento();
    }

    void MainWindow::on_checkHoje_checkStateChanged(const Qt::CheckState &arg1)
    {
        // Atualiza a tabela quando o filtro de hoje é alterado
        atualizarTabelaAtendimento();
    }

    void MainWindow::on_tw_atendimento_cellClicked(int row, int column)
    {
        // pegar id do agendamento selecionado
        // pesquisar esse id na tabela atendimentos, se tiver, recuperar valores, senao criar novo elemento
        QString texto;
        QString status;

        int id = ui->tw_atendimento->item(row, 0)->text().toInt();
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_atendimentos WHERE id_agendamento = :id_agendamento");
        query.bindValue(":id_agendamento", id);

        status = ui->tw_atendimento->item(row, 6)->text(); // Pega o valor da sexta coluna
        if(status == "Realizada") {
            ui->radioRealizado->setChecked(true);
        } else if(status == "Aguardando"){
            ui->radioAguardando->setChecked(true);
        } else { // paciente ausente
            ui->radioAusente->setChecked(true);
        }

        if (query.exec()) {
            if (query.next()) {
                texto = query.value(1).toString(); // Pega o valor da segunda coluna
                ui->textEdit->setText(texto);
            } else {
                ui->textEdit->clear();
            }
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }
    }

    void MainWindow::on_btnSalvar_clicked()
    {
        QString texto;
        int row = ui->tw_atendimento->currentRow();
        if (row == -1) {
            qDebug() << "Nenhuma linha selecionada.";
            return;
        }

        int id = ui->tw_atendimento->item(row, 0)->text().toInt();
        texto = ui->textEdit->toPlainText();

        QSqlQuery query;
        query.prepare("SELECT * FROM tb_atendimentos WHERE id_agendamento = :id_agendamento");
        query.bindValue(":id_agendamento", id);

        if (query.exec()) {
            if (query.next()) {
                qDebug() << "entrou 1";
                // Atualiza o registro existente
                query.prepare("UPDATE tb_atendimentos SET texto = :texto WHERE id_agendamento = :id_agendamento");
                query.bindValue(":id_agendamento", id);
                query.bindValue(":texto", texto);
            } else {
                qDebug() << "entrou 2";
                // Insere um novo registro
                query.prepare("INSERT INTO tb_atendimentos (id_agendamento, texto) " "VALUES (:id_agendamento, :texto)");
                query.bindValue(":id_agendamento", id);
                query.bindValue(":texto", texto);

            }

            qDebug() << "Dados inseridos/atualizados com sucesso.";

        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }

        if (query.exec()) {
            qDebug() << "query 1 foi";
        } else {
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }

        QSqlQuery query_2;
        query_2.prepare("UPDATE tb_agendamentos SET status_sessao = :status_sessao WHERE id = :id");
        query_2.bindValue(":id", id);

        if (ui->radioRealizado->isChecked()) {
            query_2.bindValue(":status_sessao", "Realizada");
        } else if (ui->radioAguardando->isChecked()) {
            query_2.bindValue(":status_sessao", "Aguardando");
        } else {
            query_2.bindValue(":status_sessao", "Ausente");
        }

        if (query_2.exec()) {
            QMessageBox::information(this, " ", "Atendimento Salvo!");
        } else {
            qDebug() << "Erro ao executar a query:" << query_2.lastError().text();
        }

        ui->textEdit->clear();

        atualizarTabelaAtendimento();

        ui->tw_atendimento->selectRow(row);
    }

    void MainWindow::on_btnDesfazer_clicked()
{
    int row = ui->tw_atendimento->currentRow();

    if (row != -1) {
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Desfazer Mudanças", "Tem certeza que deseja desfazer as mudanças?", QMessageBox::Yes | QMessageBox::No);
            if (resposta == QMessageBox::Yes) {
                on_tw_atendimento_cellClicked(row, 0);
            }
    } else {
        qDebug() << "Nenhuma linha selecionada.";

    }
}

// FIM DA PÁGINA ATENDIMENTO


/////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "PACIENTES"

void MainWindow::on_btnPacientes_clicked()
{
    if(getLogado()){
        setButtonHighlight(ui->btnPacientes);                                                                              // ALTERAR A COR DE DESTAQUE DO BOTÃO
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
            ui->tw_pacientes->setRowHeight(tb_linha,30);

            tb_linha++;
        }

        QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
        ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);
        ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_pacientes->verticalHeader()->setVisible(false);

        // Estilizando a tabela com CSS
        ui->tw_pacientes->setStyleSheet(
            "QTableWidget {"
            "    border: 3px solid #dcdcdc;"
            "    border-radius: 10px;"
            "    background-color: #ffffff;"
            "    gridline-color: #dcdcdc;"
            "}"
            "QHeaderView::section {"
            "    background-color: #f0f0f0;"
            "    border: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "    border-radius: 5px;"
            "}"
            "QTableWidget::item {"
            "    border-bottom: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "}"
            "QTableWidget::item:selected {"
            "    background-color: #a0c4ff;"
            "    color: #000000;"
            "}"
        );

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
    if(getLogado()){
        setButtonHighlight(ui->btnColaboradores);                                                                              // ALTERAR A COR DE DESTAQUE DO BOTÃO
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
            ui->tw_colaboradores->setRowHeight(tb_linha,30);

            tb_linha++;
        }

        QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Cargo", "NºCelular", "E-mail", "Nascimento"};
        ui->tw_colaboradores->setHorizontalHeaderLabels(cabecalho);
        ui->tw_colaboradores->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tw_colaboradores->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_colaboradores->verticalHeader()->setVisible(false);

        // Estilizando a tabela com CSS
        ui->tw_colaboradores->setStyleSheet(
            "QTableWidget {"
            "    border: 3px solid #dcdcdc;"
            "    border-radius: 10px;"
            "    background-color: #ffffff;"
            "    gridline-color: #dcdcdc;"
            "}"
            "QHeaderView::section {"
            "    background-color: #f0f0f0;"
            "    border: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "    border-radius: 5px;"
            "}"
            "QTableWidget::item {"
            "    border-bottom: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "}"
            "QTableWidget::item:selected {"
            "    background-color: #a0c4ff;"
            "    color: #000000;"
            "}"
        );

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



// MÉTODO PARA ACESSAR A PÁGINA "ATENDIMENTOS" (OBS: DECIDÍMOS MUDAR O NOME DA PÁGINA POSTERIORMENTE, POR ISSO O NOME FICOU btnRelatorio)

void MainWindow::on_btnRelatorios_clicked()
{
    if (getLogado()) {  // Verifica se o usuário está logado
        setButtonHighlight(ui->btnRelatorios);  // Destaque no botão
        ui->btnRelatorios->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Relatorios);  // Página de Relatórios
        ui->paginas->setCurrentIndex(index);               // Troca para a página de relatórios
        ui->txtRelAtendimento->clear();

        carregarRelatorios();  // Carrega todos os atendimentos na TreeWidget
    } else {
        QMessageBox::information(this, "Acesso Negado", "Contrate nosso serviço para ter acesso ao sistema!");
    }

}

////////////////////////////////////////////////////////////////


    // MÉTODOS DA PÁGINA DE "ATENDIMENTOS"

    // Configuração inicial da TreeWidget
    void MainWindow::setTreeWidget(QTreeWidget *treeWidget)
    {

        // Configuração dos cabeçalhos
        QStringList headers;
        headers << "Atendimentos";  // Cabeçalho informativo
        treeWidget->setHeaderLabels(headers);

        // Ajustes visuais
        treeWidget->setHeaderHidden(false);
        treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeWidget->setExpandsOnDoubleClick(true);
        treeWidget->setAnimated(true);
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Estilizando a TreeWidget com CSS
        treeWidget->setStyleSheet(
            "QTreeWidget {"
            "    border: 3px solid #dcdcdc;"
            "    border-radius: 10px;"
            "    background-color: #ffffff;"
            "    gridline-color: #dcdcdc;"
            "}"
            "QHeaderView::section {"
            "    background-color: #f0f0f0;"
            "    border: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "    border-radius: 5px;"
            "}"
            "QTreeWidget::item {"
            "    border-bottom: 1px solid #dcdcdc;"
            "    padding: 5px;"
            "}"
            "QTreeWidget::item:selected {"
            "    background-color: #a0c4ff;"
            "    color: #000000;"
            "}"
        );
    }



    // Método para carregar todos os atendimentos na TreeWidget
    void MainWindow::carregarRelatorios(int* idSessao)
    {
        ui->trw_atendimentos->clear();  // Limpa a TreeWidget antes de carregar os dados

        QSqlQuery query;
        QString textoRelatorio;  // Variável para armazenar o texto do relatório

        if (idSessao == nullptr) {
            // Carregar todas as sessões realizadas
            query.prepare("SELECT a.id, a.data, a.hora, a.profissional, a.paciente, t.texto "
                          "FROM tb_agendamentos a "
                          "LEFT JOIN tb_atendimentos t ON a.id = t.id_agendamento "
                          "WHERE a.status_sessao = 'Realizada' "
                          "ORDER BY a.data DESC, a.hora DESC;");  // Ordena por data e hora
        } else {
            // Carregar uma sessão específica realizada
            int sessao = *idSessao;

            query.prepare("SELECT a.id, a.data, a.hora, a.profissional, a.paciente, t.texto "
                          "FROM tb_agendamentos a "
                          "LEFT JOIN tb_atendimentos t ON a.id = t.id_agendamento "
                          "WHERE a.id = :idSessao AND a.status_sessao = 'Realizada'");
            query.bindValue(":idSessao", sessao);
        }

        if (query.exec()) {
            while (query.next()) {
                // Informações da sessão
                QString sessaoInfo = QString("Data: %1 | Hora: %2\nProfissional: %3\nPaciente: %4")
                                         .arg(query.value("data").toString())
                                         .arg(query.value("hora").toString())
                                         .arg(query.value("profissional").toString())
                                         .arg(query.value("paciente").toString());

                // Cria o item pai (sessão)
                QTreeWidgetItem *sessaoItem = new QTreeWidgetItem(ui->trw_atendimentos);
                sessaoItem->setText(0, sessaoInfo);
                sessaoItem->setData(0, Qt::UserRole, query.value("id").toInt());  // Armazena o ID da sessão

                // Texto do atendimento
                QString textoAtendimento = query.value("texto").toString();
                if (!textoAtendimento.isEmpty()) {
                    // Cria o item filho (texto do atendimento)
                    QTreeWidgetItem *atendimentoItem = new QTreeWidgetItem(sessaoItem);
                    atendimentoItem->setText(0, textoAtendimento);

                    // Adiciona o texto do atendimento ao texto do relatório
                    textoRelatorio += textoAtendimento + "\n";
                }

                // Adiciona o item pai à TreeWidget
                ui->trw_atendimentos->addTopLevelItem(sessaoItem);
            }

            if (idSessao != nullptr) {
                // Expande automaticamente a sessão
                ui->trw_atendimentos->expandAll();

                // Define o texto do relatório no TextEdit
                ui->txtRelAtendimento->setPlainText(textoRelatorio);
            }

            // Configurações visuais da TreeWidget
            setTreeWidget(ui->trw_atendimentos);

        } else {
            // Mensagem de erro caso a consulta falhe
            QMessageBox::critical(this, "Erro", "Falha ao carregar os relatórios:\n" + query.lastError().text());
        }
    }


    // Exibe detalhes do atendimento no QTextEdit ao clicar em um item da TreeWidget
    void MainWindow::on_trw_atendimentos_itemClicked(QTreeWidgetItem *item, int column)
    {
        if (item->parent()) {  // Verifica se é um item filho (texto do atendimento)
            ui->txtRelAtendimento->setText(item->text(0));
        }
    }


// FIM DA PÁGINA RELATÓRIOS


////////////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "ESTOQUE"

void MainWindow::on_btnEstoque_clicked()
{
    if(getLogado()){
        setButtonHighlight(ui->btnEstoque);                                                                              // ALTERAR A COR DE DESTAQUE DO BOTÃO
        ui->btnEstoque->setAutoFillBackground(true);

        ui->radioProduto->setChecked(true);

        ui->lineEditProduto->setText("");
        ui->spinQuantidade->setValue(0);
        ui->doubleSpinCompra->setValue(0);
        ui->doubleSpinVenda->setValue(0);
        ui->lineEditFornecedor->setText("");

        int index = ui->paginas->indexOf(ui->Estoque);                                                             // PÁGINA ESTOQUE
        ui->paginas->setCurrentIndex(index);                                                                            // ACESSANDO A PÁGINA

        QSqlQuery query;

        query.prepare("SELECT * FROM tb_estoque");                          // ACESSANDO A TABELA NO BANCO

        if(query.exec()){
            setTabelaEstoque(query);                                                                                              // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
        }else{
            qDebug() << "Erro ao executar a query:" << query.lastError().text();
        }

    } else {
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");
    }
}

void MainWindow::setTabelaEstoque(QSqlQuery &query)
{
    int tb_linha = 0;

    // Limpa os dados antigos da tabela
    ui->tw_estoque->clearContents();
    ui->tw_estoque->setRowCount(0);  // Reseta as linhas

    ui->tw_estoque->setColumnCount(6);                                                                    // SETA A TABLE EM 8 COLUNAS
    while(query.next()){

        ui->tw_estoque->insertRow(tb_linha);

        for(int i = 0; i <= 5; i++){
            ui->tw_estoque->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));          // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
        }
        ui->tw_estoque->setRowHeight(tb_linha,30);

        tb_linha++;
    }

    QStringList cabecalho = {"ID", "Produto", "Quantidade", "Valor de Compra", "Valor de Venda", "Fornecedor"};
    ui->tw_estoque->setHorizontalHeaderLabels(cabecalho);
    ui->tw_estoque->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_estoque->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_estoque->verticalHeader()->setVisible(false);

    // Estilizando a tabela com CSS
    ui->tw_estoque->setStyleSheet(
        "QTableWidget {"
        "    border: 3px solid #dcdcdc;"
        "    border-radius: 10px;"
        "    background-color: #ffffff;"
        "    gridline-color: #dcdcdc;"
        "}"
        "QHeaderView::section {"
        "    background-color: #f0f0f0;"
        "    border: 1px solid #dcdcdc;"
        "    padding: 5px;"
        "    border-radius: 5px;"
        "}"
        "QTableWidget::item {"
        "    border-bottom: 1px solid #dcdcdc;"
        "    padding: 5px;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #a0c4ff;"
        "    color: #000000;"
        "}"
    );

    redimensionarTable(ui->tw_estoque);

}

void MainWindow::on_lineEditEstoque_textChanged(const QString &arg1)
{
    QString pesquisado = ui->lineEditEstoque->text();
    bool filtrarProduto = ui->radioProduto->isChecked();
    QSqlQuery query;

    if (filtrarProduto) {
        query.prepare("SELECT * FROM tb_estoque WHERE produto LIKE :produto");
        query.bindValue(":produto", pesquisado + "%");
    } else {
        query.prepare("SELECT * FROM tb_estoque WHERE fornecedor LIKE :fornecedor");
        query.bindValue(":fornecedor", pesquisado + "%");
    }

    if (query.exec()) {
        setTabelaEstoque(query); // CARREGANDO A TABELA NA TABLE ATRAVÉS DO MÉTODO
    } else {
        qDebug() << "Erro ao executar a query:" << query.lastError().text();
    }
}

void MainWindow::on_radioProduto_toggled(bool checked)
{
    on_lineEditEstoque_textChanged("");
}

void MainWindow::on_tw_estoque_cellClicked(int row, int column)
{
    QSqlQuery query;

    int id = ui->tw_estoque->item(row, 0)->text().toInt();

    query.prepare("SELECT * FROM tb_estoque WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            // Pegando os valores das colunas
            QString produto = query.value("produto").toString();
            int quantidade = query.value("quantidade").toInt();
            double valor_compra = query.value("valor_compra").toDouble();
            double valor_venda = query.value("valor_venda").toDouble();
            QString fornecedor = query.value("fornecedor").toString();

            qDebug() << valor_compra;
            qDebug() << valor_venda;

            ui->lineEditProduto->setText(produto);
            ui->spinQuantidade->setValue(quantidade);
            ui->doubleSpinCompra->setValue(valor_compra);
            ui->doubleSpinVenda->setValue(valor_venda);
            ui->lineEditFornecedor->setText(fornecedor);

        } else {
            qDebug() << "Nenhum resultado encontrado.";
        }
    } else {
        qDebug() << "Erro ao executar a query:" << query.lastError().text();
    }
}

void MainWindow::on_btnDesfazerEstoque_clicked()
{
    int row = ui->tw_estoque->currentRow();

    if (row != -1) {
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Desfazer Mudanças", "Tem certeza que deseja desfazer as mudanças?", QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            on_tw_estoque_cellClicked(row, 0);
        }
    } else {
        qDebug() << "Nenhuma linha selecionada.";

    }

}

void MainWindow::on_btnAtualizar_clicked()
{
    int row = ui->tw_estoque->currentRow();

    if(row != -1){

        int id = ui->tw_estoque->item(row, 0)->text().toInt();

        QString produto = ui->lineEditProduto->text();
        int quantidade = ui->spinQuantidade->value(); // Use value() instead of text().toInt()
        double valor_compra = ui->doubleSpinCompra->value(); // Use value() instead of text().toDouble()
        double valor_venda = ui->doubleSpinVenda->value(); // Use value() instead of text().toDouble()
        QString fornecedor = ui->lineEditFornecedor->text();

        QSqlQuery query;

        query.prepare("UPDATE tb_estoque SET produto = :produto, quantidade = :quantidade, valor_compra = :valor_compra, valor_venda = :valor_venda, fornecedor = :fornecedor WHERE id = :id");

        query.bindValue(":produto", produto);
        query.bindValue(":quantidade", quantidade);
        query.bindValue(":valor_compra", valor_compra);
        query.bindValue(":valor_venda", valor_venda);
        query.bindValue(":fornecedor", fornecedor);
        query.bindValue(":id", id);

        if (query.exec()) {

            on_lineEditEstoque_textChanged("");

            ui->tw_estoque->selectRow(row);

        } else {
            qDebug() << "Erro ao atualizar o produto:" << query.lastError().text();
        }

    } else {
        qDebug() << "Nenhuma linha selecionada.";
    }
}

void MainWindow::on_btnAdicionar_clicked()
{
    QString produto = ui->lineEditProdutoAdd->text();
    QString fornecedor = ui->lineEditFornecedorAdd->text();

    QSqlQuery query;

    query.prepare("INSERT INTO tb_estoque (produto, fornecedor) " "VALUES (:produto, :fornecedor)");
    query.bindValue(":produto", produto);
    query.bindValue(":fornecedor", fornecedor);

    if (query.exec()) {
        QMessageBox::information(this, " ", "Produto adicionado ao estoque com sucesso.");

        ui->lineEditProdutoAdd->clear();
        ui->lineEditFornecedorAdd->clear();

        on_lineEditEstoque_textChanged("");

    } else {
        qDebug() << "Erro ao executar a query:" << query.lastError().text();
        QMessageBox::warning(this, " ", "Erro ao adicionar o produto.");
    }

}

void MainWindow::on_btnApagar_clicked()
{
    int row = ui->tw_estoque->currentRow();

    if(row != -1){

        int id = ui->tw_estoque->item(row, 0)->text().toInt();

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Apagar Produto", "Tem certeza que deseja apagar o produto?", QMessageBox::Yes | QMessageBox::No);

        if (resposta == QMessageBox::Yes) {

            QSqlQuery query;

            query.prepare("DELETE FROM tb_estoque WHERE id = :id");
            query.bindValue(":id", id);

            if (query.exec()) {
                QMessageBox::information(this, " ", "Produto excluído com sucesso.");
                ui->tw_estoque->removeRow(row);

                ui->lineEditProduto->setText("");
                ui->spinQuantidade->setValue(0);
                ui->doubleSpinCompra->setValue(0);
                ui->doubleSpinVenda->setValue(0);
                ui->lineEditFornecedor->setText("");

            } else {
                QMessageBox::warning(this, " ", "Erro ao excluir o produto.");
                qDebug() << "Erro ao executar a query:" << query.lastError().text();
            }

        }

    } else {
        qDebug() << "Nenhuma linha selecionada.";
    }
}

// FIM DA PÁGINA FORNCEDORES


///////////////////////////////////////////////////
