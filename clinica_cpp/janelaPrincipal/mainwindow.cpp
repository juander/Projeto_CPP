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

void MainWindow::abrirPdf(const QString &link)                                                            // Método para abrir o PDF
{                                                                                                         // Abre a função
    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/guide.pdf";     // Caminho temporário para salvar o PDF

    QFile::copy(":/extraFiles/guide.pdf", tempPath);                                                      // Copia o arquivo PDF do recurso para o caminho temporário

    QDesktopServices::openUrl(QUrl::fromLocalFile(tempPath));                                             // Abre o arquivo PDF
}  

//////////////////////////////////////////


// MÉTODO PARA FORMATAR A PÁGINA PRINCIPAL E DEFINIR A PÁGINA DE INÍCIO

void MainWindow::janelaFormatada()                                                                        // Método para formatar a janela
{                                                                                                         // Abre a função
    ui->paginas->tabBar()->setVisible(false);                                                             // Deixa os ícones das páginas da TabWidget invisíveis

    ui->tab_relatorios->tabBar()->setVisible(false);                                                      // Mesma coisa para a outra TabWidget

    QPixmap logo(":/icons/logo.png");                                                                     // Carrega o logo
    ui->logo->setPixmap(logo.scaled(105, 105, Qt::KeepAspectRatio, Qt::SmoothTransformation));            // Define o logo redimensionado

    ui->labelPdf->setText("<a href=\"guide.pdf\">Instruções de uso</a>");                                 // Define o texto do link para o PDF
    ui->labelPdf->setTextInteractionFlags(Qt::LinksAccessibleByMouse);                                    // Permite interação com o link
    ui->labelPdf->setOpenExternalLinks(false);                                                            // Para capturar o clique no link

    connect(ui->labelPdf, &QLabel::linkActivated, this, &MainWindow::abrirPdf);                           // Conecta o sinal linkActivated ao slot

    QPixmap img(":/extraFiles/imgInicial.jpg");                                                           // Carrega a imagem inicial
    ui->imgInicial->setPixmap(img.scaled(500, 750, Qt::KeepAspectRatio, Qt::SmoothTransformation));       // Define a imagem inicial redimensionada

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);                        // Adiciona efeito de sombra ao frame superior
    shadowEffect->setBlurRadius(15);                                                                      // Aumenta o desfoque para 15px
    shadowEffect->setOffset(0, 7);                                                                        // Desloca a sombra 7px para baixo
    shadowEffect->setColor(QColor(0, 0, 0, 150));                                                         // Define cor da sombra com maior opacidade

    ui->frameSuperior->setGraphicsEffect(shadowEffect);                                                   // Aplica o efeito de sombra ao frame superior

    ui->frameSuperior->raise();                                                                           // Traz o frame superior para frente
    ui->frameLateral->lower();                                                                            // Envia o frame lateral para trás

    ui->calendarioAgenda->setStyleSheet(                                                                  // Estiliza o calendário
        "QCalendarWidget QWidget#qt_calendar_navigationbar {"
        "    background-color: #dcdcdc;"                                                                  // Cor de fundo da barra de navegação
        "}"
        "QCalendarWidget QToolButton {"
        "    color: #000000;"                                                                             // Cor do texto dos botões
        "}"
        "QCalendarWidget QAbstractItemView:enabled {"
        "    selection-background-color: #a0c4ff;"                                                        // Cor de fundo da seleção
        "    selection-color: #000000;"                                                                   // Cor do texto da seleção
        "}"
    );

    QToolButton *prevMonthButton = ui->calendarioAgenda->findChild<QToolButton *>("qt_calendar_prevmonth"); // Altera o ícone das setas de navegação
    QToolButton *nextMonthButton = ui->calendarioAgenda->findChild<QToolButton *>("qt_calendar_nextmonth");

    prevMonthButton->setIcon(QIcon(":/icons/prev.png"));                                                  // Define o ícone da seta anterior
    nextMonthButton->setIcon(QIcon(":/icons/next.png"));                                                  // Define o ícone da seta próxima

    setLogado(false);                                                                                     // Define o estado de logado como falso

    on_btnInicio_clicked();                                                                               // Define a página inicial como sempre a primeira ao abrir o programa
}                                                                                                         // Fecha a função

//////////////////////////////////////////


// MÉTODO PARA REDIMENSIONAR AS TABELAS AUTOMATICAMENTE E CASO ALGO NÃO CAIBA EXIBIR O TEXTO COMPLETO AO COLOCAR O MOUSE EM CIMA

void MainWindow::redimensionarTable(QTableWidget* table)                                                   // Método para redimensionar a tabela
{                                                                                                         // Abre a função
    table->resizeColumnsToContents();                                                                     // Ajusta as colunas ao conteúdo

    for (int i = 0; i < table->columnCount(); ++i) {                                                      // Itera sobre as colunas da tabela
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);                         // Faz as colunas se expandirem para preencher a largura total da tabela
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                                // Ajusta o layout após redimensionar as colunas

    for (int row = 0; row < table->rowCount(); ++row) {                                                   // Itera sobre as linhas da tabela
        for (int col = 0; col < table->columnCount(); ++col) {                                            // Itera sobre as colunas da tabela
            QTableWidgetItem* item = table->item(row, col);                                               // Obtém o item da célula
            if (item) {                                                                                   // Verifica se o item não é nulo
                item->setToolTip(item->text());                                                           // Define o conteúdo completo da célula como o Tooltip
                item->setTextAlignment(Qt::AlignCenter);                                                  // Alinha os itens das tabelas no centro das colunas
            }
        }
    }
}   

//////////////////////////////////////////

// MÉTODOS PARA O ESTILO DOS BOTÕES

void MainWindow::resetButtonStyles()                                                                      // Método para resetar os estilos dos botões
{                                                                                                         // Abre a função
    QList<QPushButton*> botoes = {                                                                        // Lista de botões a serem resetados
        ui->btnAgenda, ui->btnAtendimento, ui->btnPacientes,
        ui->btnColaboradores, ui->btnEstoque, ui->btnRelatorios, ui->btnInicio
    };

    for (auto botao : botoes) {                                                                           // Itera sobre a lista de botões
        botao->setStyleSheet("");                                                                         // Reseta o estilo do botão
    }
}                                                                                                         // Fecha a função

void MainWindow::setButtonHighlight(QPushButton *botao)                                                   // Método para destacar o botão ativo
{                                                                                                         // Abre a função
    if (botaoAtivo != botao) {                                                                            // Verifica se o botão ativo é diferente do botão passado
        resetButtonStyles();                                                                              // Reseta os estilos dos botões
        botao->setStyleSheet("background-color: rgb(179, 213, 243);");                                    // Aplica um highlight com CSS
        botaoAtivo = botao;                                                                               // Define o botão ativo
    }
}                                                                                                         // Fecha a função

void MainWindow::setLayoutEntrar()                                                                        // Método para configurar o layout de entrada
{                                                                                                         // Abre a função
    ui->btnEntrar->setText("Entrar");                                                                     // Define o texto do botão como "Entrar"
    ui->btnEntrar->setStyleSheet(                                                                         // Define o estilo do botão
        "QPushButton {"
        "    background-color: #6db0ec; "
        "    color: #000000; "                                                                            // Transformando o botão em login
        "    border: 2px solid #dcdcdc; "
        "    border-radius: 10px; "
        "}"
        "QPushButton:hover {"
        "    background-color: #dcdcdc;"                                                                  // Cor de fundo ao passar o mouse
        "}"
    );

    ui->iconPerfil->clear();                                                                              // Limpa o ícone do perfil
    ui->txtUsuario->clear();                                                                              // Limpa o texto do usuário
    ui->txtClinica->clear();                                                                              // Limpa o texto da clínica
    ui->txtCargo->clear();                                                                                // Limpa o texto do cargo

    ui->tw_pacientes->setRowCount(0);                                                                     // Reseta as linhas da tabela de pacientes
    ui->tw_pacientes->setColumnCount(0);                                                                  // Reseta as colunas da tabela de pacientes
    ui->tw_colaboradores->setRowCount(0);                                                                 // Reseta as linhas da tabela de colaboradores
    ui->tw_colaboradores->setColumnCount(0);                                                              // Reseta as colunas da tabela de colaboradores

    on_btnInicio_clicked();                                                                               // Volta para a página inicial
}                                                                                                         // Fecha a função

void MainWindow::setLayoutSair()                                                                          // Método para configurar o layout de saída
{                                                                                                         // Abre a função
    ui->btnEntrar->setText("Sair");                                                                       // Define o texto do botão como "Sair"
    ui->btnEntrar->setStyleSheet(                                                                         // Define o estilo do botão
        "QPushButton {"
        "    background-color: rgb(200, 20, 20); "
        "    color: #ffffff; "                                                                            // Transformando o botão em logout
        "    border-radius: 10px; "
        "}"
        "QPushButton:hover {"
        "    background-color: darkred;"                                                                  // Cor de fundo ao passar o mouse
        "}"
    );

    QPixmap icone(":/icons/Generic avatar.png");                                                          // Define o ícone do perfil
    ui->iconPerfil->setPixmap(icone.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));       // Redimensiona o ícone do perfil

    ui->txtUsuario->setText(getNomeUsuario());                                                            // Define o texto do usuário

    ui->txtUsuario->setStyleSheet(                                                                        // Define o estilo do texto do usuário
        "QLabel {"
        "    font-family: 'Poppins', sans-serif;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "    color: #000000;"                                                                             // Azul mais escuro
        "    letter-spacing: 1px;"
        "    text-transform: uppercase;"
        "}"
    );

    ui->txtCargo->setText(" - " + cargo_usuario);                                                         // Define o texto do cargo

    ui->txtCargo->setStyleSheet(                                                                          // Define o estilo do texto do cargo
        "QLabel {"
        "    font-family: 'Poppins', sans-serif;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "    color: #000000;"                                                                             // Azul mais escuro
        "    letter-spacing: 1px;"
        "    text-transform: uppercase;"
        "}"
    );

    ui->txtClinica->setText(clinica_usuario);                                                             // Define o texto da clínica

    ui->txtClinica->setStyleSheet(                                                                        // Define o estilo do texto da clínica
        "QLabel {"
        "    font-family: 'Poppins', sans-serif;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "    color: #000000;"                                                                             // Azul mais escuro
        "    letter-spacing: 1px;"
        "    text-transform: uppercase;"
        "}"
    );
}                                                                                                         // Fecha a função

//////////////////////////////////////////

// MÉTODO PARA ATUALIZAR O SISTEMA QUANDO O USUÁRIO LOGAR

void MainWindow::usuarioEntrou(){

    setLogado(true);                                                                                              // ESTADO DE LOGIN TRUE

    setLayoutSair();

    ui->calendarioAgenda->setSelectedDate(QDate::currentDate());

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

void MainWindow::on_btnAgenda_clicked()                                                                  // Função chamada quando o botão "Agenda" é clicado
{                                                                                                         // Abre a função
    if(getLogado()) {                                                                                     // Verifica se o usuário está logado
        setButtonHighlight(ui->btnAgenda);                                                                // Altera a cor de destaque do botão
        ui->btnAgenda->setAutoFillBackground(true);

        int index = ui->paginas->indexOf(ui->Agenda);                                                     // Obtém o índice da página "Agenda"
        ui->paginas->setCurrentIndex(index);                                                              // Acessa a página "Agenda"

        QSqlQuery query;                                                                                  // Cria um objeto para executar a query SQL

        QDate data = ui->calendarioAgenda->selectedDate();                                                // Obtém a data selecionada no calendário

        ui->checkDataAgenda->setChecked(true);                                                            // Marca o checkbox "Data"
        ui->checkMinhaAgenda->setChecked(true);                                                           // Marca o checkbox "Minha Agenda"
        ui->comboBoxStatusAgenda->setCurrentIndex(0);                                                     // Define o status como "Aguardando"

        query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
                      "AND data = :data and status_sessao = :status ORDER BY data ASC, hora ASC");        // Prepara a query para selecionar os agendamentos do profissional na data especificada

        query.bindValue(":id_profissional", getIdUsuario());                                               // Vincula o valor do ID do profissional à query
        query.bindValue(":data", data.toString("dd/MM/yyyy"));                                             // Vincula o valor da data à query
        query.bindValue(":status", "Aguardando");                                                          // Vincula o valor do status à query

        if(query.exec()) {                                                                                // Executa a query e verifica se foi bem-sucedida
            setAgenda(query);                                                                             // Carrega a tabela na TableWidget através do método
        } else {                                                                                          // Caso a query falhe
            qDebug() << "Erro ao executar a query:" << query.lastError().text();                          // Loga o erro no console de debug
        }

    } else {                                                                                              // Caso o usuário não esteja logado
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");        // Exibe uma mensagem informando que o serviço deve ser contratado
    }
}                                                                                                         // Fecha a função

////////////////////////////////////////////////////////////////////

// MÉTODOS DA PÁGINA "AGENDA"

////////////////////////////////////////////////////////////////


    // MÉTODO PARA AJUSTAR A TABLE DA AGENDA

void MainWindow::setAgenda(QSqlQuery &query)                                                              // Método para configurar a tabela de agenda
{                                                                                                         // Abre a função
    int tb_linha = 0;                                                                                     // Inicializa a variável para contar as linhas

    ui->tw_agenda->clearContents();                                                                       // Limpa os dados antigos da tabela
    ui->tw_agenda->setRowCount(0);                                                                        // Reseta as linhas

    ui->tw_agenda->setColumnCount(7);                                                                     // Define a tabela com 7 colunas
    while(query.next()) {                                                                                 // Itera sobre os resultados da query

        ui->tw_agenda->insertRow(tb_linha);                                                               // Insere uma nova linha na tabela

        for(int i = 0; i <= 6; i++) {                                                                     // Loop que preenche a tabela com os dados do banco
            ui->tw_agenda->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));         // Define o item da tabela com o valor da query
        }
        ui->tw_agenda->setRowHeight(tb_linha, 30);                                                        // Define a altura da linha

        tb_linha++;                                                                                       // Incrementa a contagem de linhas
    }

    QStringList cabecalho = {"ID", "Profissional", "Paciente", "Especialidade", "Data", "Hora", "Status"}; // Define os cabeçalhos da tabela
    ui->tw_agenda->setHorizontalHeaderLabels(cabecalho);                                                  // Define os cabeçalhos horizontais
    ui->tw_agenda->setEditTriggers(QAbstractItemView::NoEditTriggers);                                    // Desabilita a edição dos itens
    ui->tw_agenda->setSelectionBehavior(QAbstractItemView::SelectRows);                                   // Define o comportamento de seleção para selecionar linhas inteiras
    ui->tw_agenda->verticalHeader()->setVisible(false);                                                   // Oculta o cabeçalho vertical

    ui->tw_agenda->setStyleSheet(                                                                         // Estilizando a tabela com CSS
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

    redimensionarTable(ui->tw_agenda);                                                                    // Redimensiona a tabela
}                                                                                                         // Fecha a função

void MainWindow::filtrarAgenda()                                                                          // Método de pesquisa para filtrar a agenda
{                                                                                                         // Abre a função
    QString pesquisado = ui->lineEditAgenda->text();                                                      // Obtém o texto do campo de pesquisa
    bool filtrarData = ui->checkDataAgenda->isChecked();                                                  // Verifica se o filtro por data está marcado
    bool filtrarMinhaAgenda = ui->checkMinhaAgenda->isChecked();                                          // Verifica se o filtro "Minha Agenda" está marcado
    QString opcaoSelecionada = ui->comboBoxAgenda->currentText();                                         // Obtém a opção selecionada no comboBox
    QString statusSelecionado = ui->comboBoxStatusAgenda->currentText();                                  // Obtém o status selecionado no comboBox
    QDate data = ui->calendarioAgenda->selectedDate();                                                    // Obtém a data selecionada no calendário
    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL

    if (statusSelecionado == "Paciente ausente") {                                                        // Verifica se o status é "Paciente ausente"
        statusSelecionado = "Ausente";                                                                    // Altera o status para "Ausente"
    }

    QString queryString = "SELECT * FROM tb_agendamentos WHERE status_sessao = :status";                  // Base da query

    if (filtrarMinhaAgenda) {                                                                             // Verifica se o filtro "Minha Agenda" está marcado
        queryString += " AND id_profissional = :id_profissional";                                         // Adiciona o filtro por ID do profissional
    }

    if (filtrarData) {                                                                                    // Verifica se o filtro por data está marcado
        queryString += " AND data = :data";                                                               // Adiciona o filtro por data
    }

    if (!pesquisado.isEmpty()) {                                                                          // Verifica se o campo de pesquisa não está vazio
        if (opcaoSelecionada == "Profissional") {                                                         // Verifica se a opção selecionada é "Profissional"
            queryString += " AND profissional LIKE :pesquisado";                                          // Adiciona o filtro por profissional
        } else if (opcaoSelecionada == "Paciente") {                                                      // Verifica se a opção selecionada é "Paciente"
            queryString += " AND paciente LIKE :pesquisado";                                              // Adiciona o filtro por paciente
        } else if (opcaoSelecionada == "Especialidade") {                                                 // Verifica se a opção selecionada é "Especialidade"
            queryString += " AND especialidade LIKE :pesquisado";                                         // Adiciona o filtro por especialidade
        }
    }

    queryString += " ORDER BY data ASC, hora ASC";                                                        // Ordena por data e hora
    query.prepare(queryString);                                                                           // Prepara a query

    query.bindValue(":status", statusSelecionado);                                                        // Vincula o valor do status à query

    if (filtrarMinhaAgenda) {                                                                             // Verifica se o filtro "Minha Agenda" está marcado
        int id_profissional = getIdUsuario();                                                             // Obtém o ID do profissional
        query.bindValue(":id_profissional", id_profissional);                                             // Vincula o valor do ID do profissional à query
        qDebug() << "Filtro 'Minha Agenda' ativado - ID do Profissional:" << id_profissional;             // Loga a mensagem no console de debug
    }

    if (filtrarData) {                                                                                    // Verifica se o filtro por data está marcado
        QString dataFormatada = data.toString("dd/MM/yyyy");                                              // Formata a data
        query.bindValue(":data", dataFormatada);                                                          // Vincula o valor da data à query
        qDebug() << "Filtro por Data ativado - Data selecionada:" << dataFormatada;                       // Loga a mensagem no console de debug
    }

    if (!pesquisado.isEmpty()) {                                                                          // Verifica se o campo de pesquisa não está vazio
        QString pesquisadoFinal = pesquisado + "%";                                                       // Adiciona o caractere curinga
        query.bindValue(":pesquisado", pesquisadoFinal);                                                  // Vincula o valor do campo de pesquisa à query
        qDebug() << "Filtro de Pesquisa ativado - Opção:" << opcaoSelecionada << "- Valor:" << pesquisadoFinal; // Loga a mensagem no console de debug
    }

    qDebug() << "Query Final construída:" << queryString;                                                 // Loga a query final no console de debug

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        qDebug() << "Query executada com sucesso!";                                                       // Loga a mensagem de sucesso no console de debug
        setAgenda(query);                                                                                 // Atualiza a tabela com os dados ordenados
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
    }
}                                                                                                         // Fecha a função

void MainWindow::on_checkDataAgenda_checkStateChanged(const Qt::CheckState &arg1)                         // Função chamada quando o estado do checkbox "Data" é alterado
{                                                                                                         // Abre a função
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_checkMinhaAgenda_stateChanged(int arg1)                                               // Função chamada quando o estado do checkbox "Minha Agenda" é alterado
{                                                                                                         // Abre a função
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_comboBoxAgenda_currentTextChanged(const QString &arg1)                                // Função chamada quando o texto do comboBox "Agenda" é alterado
{                                                                                                         // Abre a função
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_comboBoxStatusAgenda_currentTextChanged(const QString &arg1)                          // Função chamada quando o texto do comboBox "Status" é alterado
{                                                                                                         // Abre a função
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_lineEditAgenda_textChanged(const QString &arg1)                                       // Função chamada quando o texto do campo de pesquisa é alterado
{                                                                                                         // Abre a função
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_calendarioAgenda_clicked(const QDate &date)                                           // Função chamada quando uma data no calendário é clicada
{                                                                                                         // Abre a função
    ui->calendarioAgenda->setSelectedDate(date);                                                          // Define a data selecionada no calendário
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_btnAgendar_clicked()                                                                  // Função chamada quando o botão "Agendar" é clicado
{                                                                                                         // Abre a função
    cadastroSessao *cadastrarSessao = new cadastroSessao(this, "Cadastrar");                              // Cria a janela de cadastro de sessão

    bool connected = connect(cadastrarSessao, &cadastroSessao::sessaoCadastrada,                          // Conecta o sinal ao slot que adiciona a sessão na tabela
                             this, &MainWindow::adicionarSessaoNaTabela);

    if (!connected) {                                                                                     // Verifica se a conexão falhou
        qDebug() << "Erro ao conectar o sinal sessaoCadastrada";                                          // Loga a mensagem de erro no console de debug
    }

    cadastrarSessao->show();                                                                              // Exibe a janela de cadastro de sessão
}                                                                                                         // Fecha a função

void MainWindow::adicionarSessaoNaTabela()                                                                // Método para adicionar uma sessão na tabela
{                                                                                                         // Abre a função
    filtrarAgenda();                                                                                      // Chama a função de filtro da agenda
}                                                                                                         // Fecha a função

void MainWindow::on_tw_agenda_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) // Função chamada quando a célula atual da tabela de agenda é alterada
{                                                                                                         // Abre a função
    if (currentRow >= 0 && ui->tw_agenda->item(currentRow, 0)) {                                          // Verifica se a linha atual é válida e se a célula não está vazia
        QString idStr = ui->tw_agenda->item(currentRow, 0)->text();                                       // Obtém o texto da célula
        setIdSessao(idStr.toInt());                                                                       // Define o ID da sessão
    } else {                                                                                              // Caso contrário
        setIdSessao();                                                                                    // Define o valor inválido -1
    }
}                                                                                                         // Fecha a função

void MainWindow::on_btnEditarAgenda_clicked()                                                             // Função chamada quando o botão "Editar" é clicado
{                                                                                                         // Abre a função
    int linha = ui->tw_agenda->currentRow();                                                              // Obtém a linha atual da tabela de agenda

    if (getIdSessao() != -1 && linha >= 0) {                                                              // Verifica se o ID da sessão é válido e se a linha é válida
        cadastroSessao *cadastrarSessao = new cadastroSessao(this, "Editar", getIdSessao());              // Cria a janela de edição de sessão

        connect(cadastrarSessao, &cadastroSessao::sessaoEditada,                                          // Conecta o sinal de edição ao slot de atualização
                this, &MainWindow::atualizarSessaoNaTabela);

        cadastrarSessao->show();                                                                          // Exibe a janela de edição de sessão
    } else {                                                                                              // Caso contrário
        QMessageBox::warning(this, " ", "Selecione uma sessão para editar.");                             // Exibe uma mensagem de aviso
    }
}                                                                                                         // Fecha a função

void MainWindow::atualizarSessaoNaTabela()                                                                // Método para atualizar uma sessão na tabela
{                                                                                                         // Abre a função
    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL
    query.prepare("SELECT * FROM tb_agendamentos WHERE id = :id");                                        // Prepara a query para selecionar a sessão com o ID especificado
    query.bindValue(":id", getIdSessao());                                                                // Vincula o valor do ID da sessão à query

    int tb_linha = ui->tw_agenda->currentRow();                                                           // Obtém a linha atual da tabela de agenda

    if (query.exec() && query.first()) {                                                                  // Executa a query e verifica se foi bem-sucedida e se há resultados
        for (int i = 0; i < ui->tw_agenda->columnCount(); i++) {                                          // Itera sobre as colunas da tabela
            ui->tw_agenda->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));         // Preenche os dados do banco na tabela
        }
        redimensionarTable(ui->tw_agenda);                                                                // Redimensiona a tabela
    } else {                                                                                              // Caso a query falhe
        QMessageBox::warning(this, " ", "Erro ao buscar os dados da sessão.");                            // Exibe uma mensagem de aviso
    }
}                                                                                                         // Fecha a função

void MainWindow::on_btnVerRelatorio_clicked()                                                             // Função chamada quando o botão "Ver Relatório" é clicado
{                                                                                                         // Abre a função
    int linhaSelecionada = ui->tw_agenda->currentRow();                                                   // Obtém a linha selecionada da tabela de agenda
    if (linhaSelecionada < 0) {                                                                           // Verifica se nenhuma linha está selecionada
        QMessageBox::warning(this, "Aviso", "Selecione uma sessão para ver o relatório.");                // Exibe uma mensagem de aviso
        return;                                                                                           // Retorna sem fazer nada
    }

    QString statusSessao = ui->tw_agenda->item(linhaSelecionada, 6)->text();                              // Obtém o status da sessão
    if (statusSessao != "Realizada") {                                                                    // Verifica se o status não é "Realizada"
        QMessageBox::warning(this, "Aviso", "A sessão selecionada ainda não foi realizada.");             // Exibe uma mensagem de aviso
        return;                                                                                           // Retorna sem fazer nada
    }

    int idSessao = ui->tw_agenda->item(linhaSelecionada, 0)->text().toInt();                              // Obtém o ID da sessão

    ui->txtRelAtendimento->clear();                                                                       // Limpa o campo de texto do relatório

    carregarRelatorios(&idSessao);                                                                        // Carrega os relatórios da sessão

    ui->paginas->setCurrentWidget(ui->Relatorios);                                                        // Acessa a página de relatórios
    ui->tab_relatorios->setCurrentWidget(ui->Atendimentos);                                               // Acessa a aba de atendimentos
    resetButtonStyles();                                                                                  // Reseta os estilos dos botões
    ui->btnRelatorios->setStyleSheet("background-color: rgb(179, 213, 243);");                            // Altera a cor de destaque do botão de relatórios
    ui->btnRelatorios->setAutoFillBackground(true);                                                       // Define o preenchimento automático do fundo do botão
}                                                                                                         // Fecha a função



// FIM DA PÁGINA AGENDA


////////////////////////////////////////////


// MÉTODO PARA ACESSAR A PÁGINA "ATENDIMENTO" (OBS MUDAMOS O NOME DA PÁGINA PARA ATENDER)

void MainWindow::on_btnAtendimento_clicked()                                                              // Função chamada quando o botão "Atendimento" é clicado
{                                                                                                         // Abre a função
    if (getLogado()) {                                                                                    // Verifica se o usuário está logado
        setButtonHighlight(ui->btnAtendimento);                                                           // Altera a cor de destaque do botão
        ui->btnAtendimento->setAutoFillBackground(true);

        ui->checkHoje->setChecked(true);                                                                  // Marca o checkbox "Hoje"

        int index = ui->paginas->indexOf(ui->Atendimento);                                                // Obtém o índice da página "Atendimento"
        ui->paginas->setCurrentIndex(index);                                                              // Acessa a página "Atendimento"

        atualizarTabelaAtendimento();                                                                     // Atualiza a tabela com filtros e ordenação
    } else {                                                                                              // Caso o usuário não esteja logado
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");        // Exibe uma mensagem informando que o serviço deve ser contratado
    }

    ui->textEdit->clear();                                                                                // Limpa o campo de texto
}                                                                                                         // Fecha a função

void MainWindow::setTabelaAtendimento(QSqlQuery &query)                                                   // Método para configurar a tabela de atendimentos
{                                                                                                         // Abre a função
    int tb_linha = 0;                                                                                     // Inicializa a variável para contar as linhas

    ui->tw_atendimento->clearContents();                                                                  // Limpa os dados antigos da tabela
    ui->tw_atendimento->setRowCount(0);                                                                   // Reseta as linhas

    ui->tw_atendimento->setColumnCount(7);                                                                // Define a tabela com 7 colunas
    while (query.next()) {                                                                                // Itera sobre os resultados da query
        ui->tw_atendimento->insertRow(tb_linha);                                                          // Insere uma nova linha na tabela

        for (int i = 0; i <= 6; i++) {                                                                    // Loop que preenche a tabela com os dados do banco
            ui->tw_atendimento->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));    // Define o item da tabela com o valor da query
        }
        ui->tw_atendimento->setRowHeight(tb_linha, 30);                                                   // Define a altura da linha

        tb_linha++;                                                                                       // Incrementa a contagem de linhas
    }

    QStringList cabecalho = {"ID", "Profissional", "Paciente", "Especialidade", "Data", "Hora", "Status"}; // Define os cabeçalhos da tabela
    ui->tw_atendimento->setHorizontalHeaderLabels(cabecalho);                                             // Define os cabeçalhos horizontais
    ui->tw_atendimento->setEditTriggers(QAbstractItemView::NoEditTriggers);                               // Desabilita a edição dos itens
    ui->tw_atendimento->setSelectionBehavior(QAbstractItemView::SelectRows);                              // Define o comportamento de seleção para selecionar linhas inteiras
    ui->tw_atendimento->verticalHeader()->setVisible(false);                                              // Oculta o cabeçalho vertical

    ui->tw_atendimento->setStyleSheet(                                                                    // Estilizando a tabela com CSS
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

    redimensionarTable(ui->tw_atendimento);                                                               // Redimensiona a tabela
}                                                                                                         // Fecha a função

void MainWindow::atualizarTabelaAtendimento()                                                             // Método para atualizar a tabela de atendimentos
{                                                                                                         // Abre a função
    QString pesquisado = ui->lineEditAtendimento->text();                                                 // Obtém o texto do campo de pesquisa
    bool filtrarHoje = ui->checkHoje->isChecked();                                                        // Verifica se o filtro "Hoje" está marcado
    QDate data = QDate::currentDate();                                                                    // Obtém a data atual
    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL

    QString statusSelecionado = ui->comboBoxAtender->currentText();                                       // Obtém o status selecionado no comboBox

    if (statusSelecionado == "Paciente ausente") {                                                        // Verifica se o status é "Paciente ausente"
        statusSelecionado = "Ausente";                                                                    // Altera o status para "Ausente"
    }

    if (pesquisado.isEmpty()) {                                                                           // Verifica se o campo de pesquisa está vazio
        if (!filtrarHoje) {                                                                               // Verifica se o filtro "Hoje" não está marcado
            query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
            "AND status_sessao = :status_sessao ORDER BY data ASC, hora ASC");                             // Prepara a query para selecionar todos os agendamentos do profissional com o status especificado
            query.bindValue(":id_profissional", getIdUsuario());                                           // Vincula o valor do ID do profissional à query
            query.bindValue(":status_sessao", statusSelecionado);                                          // Vincula o valor do status à query
        } else {                                                                                          // Caso o filtro "Hoje" esteja marcado
            query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
            "AND data = :data AND status_sessao = :status_sessao ORDER BY data ASC, hora ASC");            // Prepara a query para selecionar todos os agendamentos do profissional com o status especificado e a data atual
            query.bindValue(":id_profissional", getIdUsuario());                                           // Vincula o valor do ID do profissional à query
            query.bindValue(":data", data.toString("dd/MM/yyyy"));                                         // Vincula o valor da data à query
            query.bindValue(":status_sessao", statusSelecionado);                                          // Vincula o valor do status à query
        }
    } else {                                                                                              // Caso o campo de pesquisa não esteja vazio
        if (!filtrarHoje) {                                                                               // Verifica se o filtro "Hoje" não está marcado
            query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
            "AND paciente LIKE :paciente AND status_sessao = :status_sessao ORDER BY data ASC, hora ASC"); // Prepara a query para selecionar todos os agendamentos do profissional com o status especificado e o paciente pesquisado
            query.bindValue(":id_profissional", getIdUsuario());                                           // Vincula o valor do ID do profissional à query
            query.bindValue(":paciente", pesquisado + "%");                                                // Vincula o valor do paciente à query
            query.bindValue(":status_sessao", statusSelecionado);                                          // Vincula o valor do status à query
        } else {                                                                                          // Caso o filtro "Hoje" esteja marcado
            query.prepare("SELECT * FROM tb_agendamentos WHERE id_profissional = :id_profissional "
            "AND data = :data AND paciente LIKE :paciente AND status_sessao = :status_sessao ORDER BY data ASC, hora ASC"); // Prepara a query para selecionar todos os agendamentos do profissional com o status especificado, a data atual e o paciente pesquisado
            query.bindValue(":id_profissional", getIdUsuario());                                           // Vincula o valor do ID do profissional à query
            query.bindValue(":data", data.toString("dd/MM/yyyy"));                                         // Vincula o valor da data à query
            query.bindValue(":paciente", pesquisado + "%");                                                // Vincula o valor do paciente à query
            query.bindValue(":status_sessao", statusSelecionado);                                          // Vincula o valor do status à query
        }
    }

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        setTabelaAtendimento(query);                                                                      // Atualiza a tabela com os dados ordenados
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
    }
}                                                                                                         // Fecha a função

void MainWindow::on_comboBoxAtender_currentIndexChanged(int index)                                        // Função chamada quando o índice do comboBox é alterado
{                                                                                                         // Abre a função
    ui->lineEditAtendimento->clear();                                                                     // Limpa o campo de pesquisa
    atualizarTabelaAtendimento();                                                                         // Atualiza a tabela com base no estado atual dos filtros
}                                                                                                         // Fecha a função

void MainWindow::on_lineEditAtendimento_textChanged(const QString &arg1)                                  // Função chamada quando o texto do campo de pesquisa é alterado
{                                                                                                         // Abre a função
    atualizarTabelaAtendimento();                                                                         // Atualiza a tabela com a pesquisa
}                                                                                                         // Fecha a função

void MainWindow::on_checkHoje_checkStateChanged(const Qt::CheckState &arg1)                               // Função chamada quando o estado do checkbox "Hoje" é alterado
{                                                                                                         // Abre a função
    atualizarTabelaAtendimento();                                                                         // Atualiza a tabela quando o filtro de hoje é alterado
}                                                                                                         // Fecha a função

void MainWindow::on_tw_atendimento_cellClicked(int row, int column)                                       // Função chamada quando uma célula da tabela de atendimento é clicada
{                                                                                                         // Abre a função
    QString texto;                                                                                        // Variável para armazenar o texto do atendimento
    QString status;                                                                                       // Variável para armazenar o status do atendimento

    int id = ui->tw_atendimento->item(row, 0)->text().toInt();                                            // Obtém o ID do agendamento selecionado
    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL
    query.prepare("SELECT * FROM tb_atendimentos WHERE id_agendamento = :id_agendamento");                // Prepara a query para selecionar o atendimento com o ID do agendamento
    query.bindValue(":id_agendamento", id);                                                               // Vincula o valor do ID do agendamento à query

    status = ui->tw_atendimento->item(row, 6)->text();                                                    // Pega o valor da sexta coluna (status)
    if(status == "Realizada") {                                                                           // Verifica se o status é "Realizada"
        ui->radioRealizado->setChecked(true);                                                             // Marca o radio button "Realizado"
    } else if(status == "Aguardando"){                                                                    // Verifica se o status é "Aguardando"
        ui->radioAguardando->setChecked(true);                                                            // Marca o radio button "Aguardando"
    } else {                                                                                              // Caso o status seja "Ausente"
        ui->radioAusente->setChecked(true);                                                               // Marca o radio button "Ausente"
    }

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        if (query.next()) {                                                                               // Verifica se há resultados
            texto = query.value(1).toString();                                                            // Pega o valor da segunda coluna (texto)
            ui->textEdit->setText(texto);                                                                 // Define o texto do QTextEdit com o texto do atendimento
        } else {                                                                                          // Caso não haja resultados
            ui->textEdit->clear();                                                                        // Limpa o QTextEdit
        }
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
    }
}                                                                                                         // Fecha a função

void MainWindow::on_btnSalvar_clicked()                                                                   // Função chamada quando o botão "Salvar" é clicado
{                                                                                                         // Abre a função
    QString texto;                                                                                        // Variável para armazenar o texto do atendimento
    int row = ui->tw_atendimento->currentRow();                                                           // Obtém a linha selecionada na tabela de atendimento
    if (row == -1) {                                                                                      // Verifica se nenhuma linha está selecionada
        qDebug() << "Nenhuma linha selecionada.";                                                         // Loga a mensagem no console de debug
        return;                                                                                           // Retorna sem fazer nada
    }

    int id = ui->tw_atendimento->item(row, 0)->text().toInt();                                            // Obtém o ID do agendamento selecionado
    texto = ui->textEdit->toPlainText();                                                                  // Obtém o texto do QTextEdit

    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL
    query.prepare("SELECT * FROM tb_atendimentos WHERE id_agendamento = :id_agendamento");                // Prepara a query para selecionar o atendimento com o ID do agendamento
    query.bindValue(":id_agendamento", id);                                                               // Vincula o valor do ID do agendamento à query

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        if (query.next()) {                                                                               // Verifica se há resultados
            query.prepare("UPDATE tb_atendimentos SET texto = :texto WHERE id_agendamento = :id_agendamento"); // Prepara a query para atualizar o texto do atendimento
            query.bindValue(":id_agendamento", id);                                                       // Vincula o valor do ID do agendamento à query
            query.bindValue(":texto", texto);                                                             // Vincula o valor do texto à query
        } else {                                                                                          // Caso não haja resultados
            query.prepare("INSERT INTO tb_atendimentos (id_agendamento, texto) VALUES (:id_agendamento, :texto)"); // Prepara a query para inserir um novo atendimento
            query.bindValue(":id_agendamento", id);                                                       // Vincula o valor do ID do agendamento à query
            query.bindValue(":texto", texto);                                                             // Vincula o valor do texto à query
        }

        if (query.exec()) {                                                                               // Executa a query e verifica se foi bem-sucedida
            qDebug() << "Dados inseridos/atualizados com sucesso.";                                       // Loga a mensagem de sucesso no console de debug
        } else {                                                                                          // Caso a query falhe
            qDebug() << "Erro ao executar a query:" << query.lastError().text();                          // Loga o erro no console de debug
        }
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
    }

    QSqlQuery query_2;                                                                                    // Cria um novo objeto para executar a query SQL
    query_2.prepare("UPDATE tb_agendamentos SET status_sessao = :status_sessao WHERE id = :id");          // Prepara a query para atualizar o status da sessão
    query_2.bindValue(":id", id);                                                                         // Vincula o valor do ID do agendamento à query

    if (ui->radioRealizado->isChecked()) {                                                                // Verifica se o radio button "Realizado" está marcado
        query_2.bindValue(":status_sessao", "Realizada");                                                 // Vincula o valor "Realizada" à query
    } else if (ui->radioAguardando->isChecked()) {                                                        // Verifica se o radio button "Aguardando" está marcado
        query_2.bindValue(":status_sessao", "Aguardando");                                                // Vincula o valor "Aguardando" à query
    } else {                                                                                              // Caso o radio button "Ausente" esteja marcado
        query_2.bindValue(":status_sessao", "Ausente");                                                   // Vincula o valor "Ausente" à query
    }

    if (query_2.exec()) {                                                                                 // Executa a query e verifica se foi bem-sucedida
        QMessageBox::information(this, " ", "Atendimento Salvo!");                                        // Exibe uma mensagem informando que o atendimento foi salvo
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query_2.lastError().text();                            // Loga o erro no console de debug
    }

    ui->textEdit->clear();                                                                                // Limpa o QTextEdit

    atualizarTabelaAtendimento();                                                                         // Atualiza a tabela de atendimentos

    ui->tw_atendimento->selectRow(row);                                                                   // Seleciona a linha atual na tabela de atendimento
}                                                                                                         // Fecha a função

void MainWindow::on_btnDesfazer_clicked()                                                                 // Função chamada quando o botão "Desfazer" é clicado
{                                                                                                         // Abre a função
    int row = ui->tw_atendimento->currentRow();                                                           // Obtém a linha selecionada na tabela de atendimento

    if (row != -1) {                                                                                      // Verifica se alguma linha está selecionada
        QMessageBox::StandardButton resposta;                                                             // Cria uma variável para armazenar a resposta do usuário
        resposta = QMessageBox::question(this, "Desfazer Mudanças", "Tem certeza que deseja desfazer as mudanças?", QMessageBox::Yes | QMessageBox::No); // Exibe uma mensagem de confirmação
        if (resposta == QMessageBox::Yes) {                                                               // Verifica se o usuário confirmou a ação
            on_tw_atendimento_cellClicked(row, 0);                                                        // Chama a função que lida com o clique na célula da tabela
        }
    } else {                                                                                              // Caso nenhuma linha esteja selecionada
        qDebug() << "Nenhuma linha selecionada.";                                                         // Loga a mensagem no console de debug
    }
}                                                                                                         // Fecha a função

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

void MainWindow::setTabelaPacientes(QSqlQuery &query)                                                     // Método para configurar a tabela de pacientes
{                                                                                                         // Abre a função
    int tb_linha = 0;                                                                                     // Inicializa a variável para contar as linhas

    ui->tw_pacientes->clearContents();                                                                    // Limpa os dados antigos da tabela
    ui->tw_pacientes->setRowCount(0);                                                                     // Reseta as linhas

    ui->tw_pacientes->setColumnCount(9);                                                                  // Define a tabela com 9 colunas
    while(query.next()) {                                                                                 // Itera sobre os resultados da query

        ui->tw_pacientes->insertRow(tb_linha);                                                            // Insere uma nova linha na tabela

        for(int i = 0; i <= 8; i++) {                                                                     // Loop que preenche a tabela com os dados do banco
            ui->tw_pacientes->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));      // Define o item da tabela com o valor da query
        }
        ui->tw_pacientes->setRowHeight(tb_linha, 30);                                                     // Define a altura da linha

        tb_linha++;                                                                                       // Incrementa a contagem de linhas
    }

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"}; // Define os cabeçalhos da tabela
    ui->tw_pacientes->setHorizontalHeaderLabels(cabecalho);                                               // Define os cabeçalhos horizontais
    ui->tw_pacientes->setEditTriggers(QAbstractItemView::NoEditTriggers);                                 // Desabilita a edição dos itens
    ui->tw_pacientes->setSelectionBehavior(QAbstractItemView::SelectRows);                                // Define o comportamento de seleção para selecionar linhas inteiras
    ui->tw_pacientes->verticalHeader()->setVisible(false);                                                // Oculta o cabeçalho vertical

    ui->tw_pacientes->setStyleSheet(                                                                      // Estilizando a tabela com CSS
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

    redimensionarTable(ui->tw_pacientes);                                                                 // Redimensiona a tabela
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

        cadastroPacientes editarPaciente(this, "Editar", id);                                                                        // CRIANDO A JENELA DE EDITAR PACIENTE
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

void MainWindow::setTabelaColaboradores(QSqlQuery &query)                                                 // Método para configurar a tabela de colaboradores
{                                                                                                         // Abre a função
    int tb_linha = 0;                                                                                     // Inicializa a variável para contar as linhas

    ui->tw_colaboradores->clearContents();                                                                // Limpa os dados antigos da tabela
    ui->tw_colaboradores->setRowCount(0);                                                                 // Reseta as linhas

    ui->tw_colaboradores->setColumnCount(8);                                                              // Define a tabela com 8 colunas
    while(query.next()) {                                                                                 // Itera sobre os resultados da query

        ui->tw_colaboradores->insertRow(tb_linha);                                                        // Insere uma nova linha na tabela

        for(int i = 0; i <= 7; i++) {                                                                     // Loop que preenche a tabela com os dados do banco
            ui->tw_colaboradores->setItem(tb_linha, i, new QTableWidgetItem(query.value(i).toString()));  // Define o item da tabela com o valor da query
        }
        ui->tw_colaboradores->setRowHeight(tb_linha, 30);                                                 // Define a altura da linha

        tb_linha++;                                                                                       // Incrementa a contagem de linhas
    }

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Cargo", "NºCelular", "E-mail", "Nascimento"}; // Define os cabeçalhos da tabela
    ui->tw_colaboradores->setHorizontalHeaderLabels(cabecalho);                                           // Define os cabeçalhos horizontais
    ui->tw_colaboradores->setEditTriggers(QAbstractItemView::NoEditTriggers);                             // Desabilita a edição dos itens
    ui->tw_colaboradores->setSelectionBehavior(QAbstractItemView::SelectRows);                            // Define o comportamento de seleção para selecionar linhas inteiras
    ui->tw_colaboradores->verticalHeader()->setVisible(false);                                            // Oculta o cabeçalho vertical

    ui->tw_colaboradores->setStyleSheet(                                                                  // Estilizando a tabela com CSS
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

    redimensionarTable(ui->tw_colaboradores);                                                             // Redimensiona a tabela
}                                                                                                         // Fecha a função

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

        cadastroColaboradores editarColaborador(this, "Editar", id);                                                                // CRIANDO A JENELA DE EDITAR COLABORADOR
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

void MainWindow::setTreeWidget(QTreeWidget *treeWidget)                                                   // Configura a TreeWidget
{                                                                                                         // Abre a função
    QStringList headers;                                                                                  // Configuração dos cabeçalhos
    headers << "Atendimentos";                                                                            // Cabeçalho informativo
    treeWidget->setHeaderLabels(headers);                                                                 // Define os cabeçalhos

    treeWidget->setHeaderHidden(false);                                                                   // Ajustes visuais
    treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeWidget->setExpandsOnDoubleClick(true);
    treeWidget->setAnimated(true);
    treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    treeWidget->setStyleSheet(                                                                           // Estilizando a TreeWidget com CSS
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
}                                                                                                         // Fecha a função

void MainWindow::carregarRelatorios(int* idSessao)                                                        // Método para carregar todos os atendimentos na TreeWidget
{                                                                                                         // Abre a função
    ui->trw_atendimentos->clear();                                                                        // Limpa a TreeWidget antes de carregar os dados

    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL
    QString textoRelatorio;                                                                               // Variável para armazenar o texto do relatório

    if (idSessao == nullptr) {                                                                            // Verifica se o ID da sessão é nulo
        query.prepare("SELECT a.id, a.data, a.hora, a.profissional, a.paciente, t.texto "                 // Prepara a query para selecionar todas as sessões realizadas
                      "FROM tb_agendamentos a "
                      "LEFT JOIN tb_atendimentos t ON a.id = t.id_agendamento "
                      "WHERE a.status_sessao = 'Realizada' "
                      "ORDER BY a.data DESC, a.hora DESC;");                                              // Ordena por data e hora
    } else {                                                                                              // Caso contrário, carrega uma sessão específica
        int sessao = *idSessao;                                                                           // Obtém o ID da sessão

        query.prepare("SELECT a.id, a.data, a.hora, a.profissional, a.paciente, t.texto "                 // Prepara a query para selecionar uma sessão específica realizada
                      "FROM tb_agendamentos a "
                      "LEFT JOIN tb_atendimentos t ON a.id = t.id_agendamento "
                      "WHERE a.id = :idSessao AND a.status_sessao = 'Realizada'");
        query.bindValue(":idSessao", sessao);                                                             // Vincula o valor do ID da sessão à query
    }

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        while (query.next()) {                                                                            // Itera sobre os resultados da query
            QString sessaoInfo = QString("Data: %1 | Hora: %2\nProfissional: %3\nPaciente: %4")           // Informações da sessão
                                     .arg(query.value("data").toString())
                                     .arg(query.value("hora").toString())
                                     .arg(query.value("profissional").toString())
                                     .arg(query.value("paciente").toString());

            QTreeWidgetItem *sessaoItem = new QTreeWidgetItem(ui->trw_atendimentos);                      // Cria o item pai (sessão)
            sessaoItem->setText(0, sessaoInfo);                                                           // Define o texto do item pai
            sessaoItem->setData(0, Qt::UserRole, query.value("id").toInt());                              // Armazena o ID da sessão

            QString textoAtendimento = query.value("texto").toString();                                   // Texto do atendimento
            if (!textoAtendimento.isEmpty()) {                                                            // Verifica se o texto do atendimento não está vazio
                QTreeWidgetItem *atendimentoItem = new QTreeWidgetItem(sessaoItem);                       // Cria o item filho (texto do atendimento)
                atendimentoItem->setText(0, textoAtendimento);                                            // Define o texto do item filho

                textoRelatorio += textoAtendimento + "\n";                                                // Adiciona o texto do atendimento ao texto do relatório
            }

            ui->trw_atendimentos->addTopLevelItem(sessaoItem);                                            // Adiciona o item pai à TreeWidget
        }

        if (idSessao != nullptr) {                                                                        // Verifica se o ID da sessão não é nulo
            ui->trw_atendimentos->expandAll();                                                            // Expande automaticamente a sessão

            ui->txtRelAtendimento->setPlainText(textoRelatorio);                                          // Define o texto do relatório no TextEdit
        }

        setTreeWidget(ui->trw_atendimentos);                                                              // Configurações visuais da TreeWidget

    } else {                                                                                              // Caso a query falhe
        QMessageBox::critical(this, "Erro", "Falha ao carregar os relatórios:\n" + query.lastError().text()); // Mensagem de erro caso a consulta falhe
    }
}                                                                                                         // Fecha a função

void MainWindow::on_trw_atendimentos_itemClicked(QTreeWidgetItem *item, int column)                       // Exibe detalhes do atendimento no QTextEdit ao clicar em um item da TreeWidget
{                                                                                                         // Abre a função
    if (item->parent()) {                                                                                 // Verifica se é um item filho (texto do atendimento)
        ui->txtRelAtendimento->setText(item->text(0));                                                    // Define o texto do QTextEdit com o texto do item
    }
}                                                                                                         // Fecha a função

void MainWindow::on_btnEstoque_clicked()                                                                  // Método para acessar a página "Estoque"
{                                                                                                         // Abre a função
    if(getLogado()){                                                                                      // Verifica se o usuário está logado
        setButtonHighlight(ui->btnEstoque);                                                               // Altera a cor de destaque do botão
        ui->btnEstoque->setAutoFillBackground(true);

        ui->radioProduto->setChecked(true);                                                               // Define o filtro por produto como selecionado

        ui->lineEditProduto->setText("");                                                                 // Limpa o campo de texto do produto
        ui->spinQuantidade->setValue(0);                                                                  // Reseta o valor do spin box de quantidade
        ui->doubleSpinCompra->setValue(0);                                                                // Reseta o valor do double spin box de compra
        ui->doubleSpinVenda->setValue(0);                                                                 // Reseta o valor do double spin box de venda
        ui->lineEditFornecedor->setText("");                                                              // Limpa o campo de texto do fornecedor

        int index = ui->paginas->indexOf(ui->Estoque);                                                    // Obtém o índice da página "Estoque"
        ui->paginas->setCurrentIndex(index);                                                              // Acessa a página "Estoque"

        QSqlQuery query;                                                                                  // Cria um objeto para executar a query SQL

        query.prepare("SELECT * FROM tb_estoque");                                                        // Prepara a query para selecionar todos os produtos do estoque

        if(query.exec()){                                                                                 // Executa a query e verifica se foi bem-sucedida
            setTabelaEstoque(query);                                                                      // Carrega a tabela de estoque com os resultados da query
        }else{                                                                                            // Caso a query falhe
            qDebug() << "Erro ao executar a query:" << query.lastError().text();                          // Loga o erro no console de debug
        }

    } else {                                                                                              // Caso o usuário não esteja logado
        QMessageBox::information(this, " ", "Contrate nosso serviço para ter acesso ao sistema!");        // Exibe uma mensagem informando que o serviço deve ser contratado
    }
}                                                                                                         // Fecha a função

void MainWindow::setTabelaEstoque(QSqlQuery &query)                                                       // Método para configurar a tabela de estoque
{                                                                                                         // Abre a função
    int tb_linha = 0;                                                                                     // Inicializa a variável para contar as linhas

    ui->tw_estoque->clearContents();                                                                      // Limpa os dados antigos da tabela
    ui->tw_estoque->setRowCount(0);                                                                       // Reseta as linhas

    ui->tw_estoque->setColumnCount(6);                                                                    // Define a tabela com 6 colunas
    while(query.next()){                                                                                  // Itera sobre os resultados da query

        ui->tw_estoque->insertRow(tb_linha);                                                              // Insere uma nova linha na tabela

        for(int i = 0; i <= 5; i++){                                                                      // Loop que preenche a tabela com os dados do banco
            ui->tw_estoque->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));          // Define o item da tabela com o valor da query
        }
        ui->tw_estoque->setRowHeight(tb_linha,30);                                                        // Define a altura da linha

        tb_linha++;                                                                                       // Incrementa a contagem de linhas
    }

    QStringList cabecalho = {"ID", "Produto", "Quantidade", "Valor de Compra", "Valor de Venda", "Fornecedor"}; // Define os cabeçalhos da tabela
    ui->tw_estoque->setHorizontalHeaderLabels(cabecalho);                                                 // Define os cabeçalhos horizontais
    ui->tw_estoque->setEditTriggers(QAbstractItemView::NoEditTriggers);                                   // Desabilita a edição dos itens
    ui->tw_estoque->setSelectionBehavior(QAbstractItemView::SelectRows);                                  // Define o comportamento de seleção para selecionar linhas inteiras
    ui->tw_estoque->verticalHeader()->setVisible(false);                                                  // Oculta o cabeçalho vertical

    ui->tw_estoque->setStyleSheet(                                                                        // Estilizando a tabela com CSS
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

    redimensionarTable(ui->tw_estoque);                                                                   // Redimensiona a tabela
}                                                                                                         // Fecha a função

void MainWindow::on_lineEditEstoque_textChanged(const QString &arg1)                                      // Função chamada quando o texto do campo de pesquisa é alterado
{                                                                                                         // Abre a função
    QString pesquisado = ui->lineEditEstoque->text();                                                     // Obtém o texto do campo de pesquisa
    bool filtrarProduto = ui->radioProduto->isChecked();                                                  // Verifica se o filtro por produto está selecionado
    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL

    if (filtrarProduto) {                                                                                 // Verifica se o filtro por produto está selecionado
        query.prepare("SELECT * FROM tb_estoque WHERE produto LIKE :produto");                            // Prepara a query para selecionar produtos que correspondem ao texto pesquisado
        query.bindValue(":produto", pesquisado + "%");                                                    // Vincula o valor do produto à query
    } else {                                                                                              // Caso contrário, filtra por fornecedor
        query.prepare("SELECT * FROM tb_estoque WHERE fornecedor LIKE :fornecedor");                      // Prepara a query para selecionar fornecedores que correspondem ao texto pesquisado
        query.bindValue(":fornecedor", pesquisado + "%");                                                 // Vincula o valor do fornecedor à query
    }

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        setTabelaEstoque(query);                                                                          // Carrega a tabela de estoque com os resultados da query
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
    }
}                                                                                                         // Fecha a função

void MainWindow::on_radioProduto_toggled(bool checked)                                                    // Função chamada quando o filtro por produto é alterado
{                                                                                                         // Abre a função
    on_lineEditEstoque_textChanged("");                                                                   // Atualiza a tabela de estoque
}                                                                                                         // Fecha a função

void MainWindow::on_tw_estoque_cellClicked(int row, int column)                                           // Função chamada quando uma célula da tabela de estoque é clicada
{                                                                                                         // Abre a função
    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL

    int id = ui->tw_estoque->item(row, 0)->text().toInt();                                                // Obtém o ID do produto na linha selecionada

    query.prepare("SELECT * FROM tb_estoque WHERE id = :id");                                             // Prepara a query para selecionar o produto com o ID especificado
    query.bindValue(":id", id);                                                                           // Vincula o valor do ID à query

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        if (query.next()) {                                                                               // Verifica se há resultados
            QString produto = query.value("produto").toString();                                          // Obtém o valor da coluna "produto"
            int quantidade = query.value("quantidade").toInt();                                           // Obtém o valor da coluna "quantidade"
            double valor_compra = query.value("valor_compra").toDouble();                                 // Obtém o valor da coluna "valor_compra"
            double valor_venda = query.value("valor_venda").toDouble();                                   // Obtém o valor da coluna "valor_venda"
            QString fornecedor = query.value("fornecedor").toString();                                    // Obtém o valor da coluna "fornecedor"

            qDebug() << valor_compra;                                                                     // Loga o valor de compra no console de debug
            qDebug() << valor_venda;                                                                      // Loga o valor de venda no console de debug

            ui->lineEditProduto->setText(produto);                                                        // Define o texto do campo de produto
            ui->spinQuantidade->setValue(quantidade);                                                     // Define o valor do spin box de quantidade
            ui->doubleSpinCompra->setValue(valor_compra);                                                 // Define o valor do double spin box de compra
            ui->doubleSpinVenda->setValue(valor_venda);                                                   // Define o valor do double spin box de venda
            ui->lineEditFornecedor->setText(fornecedor);                                                  // Define o texto do campo de fornecedor

        } else {                                                                                          // Caso não haja resultados
            qDebug() << "Nenhum resultado encontrado.";                                                   // Loga a mensagem no console de debug
        }
    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
    }
}     

void MainWindow::on_btnDesfazerEstoque_clicked()                                                          // Função chamada quando o botão "Desfazer" é clicado
{                                                                                                         // Abre a função
    int row = ui->tw_estoque->currentRow();                                                               // Obtém a linha selecionada na tabela de estoque

    if (row != -1) {                                                                                      // Verifica se alguma linha está selecionada
        QMessageBox::StandardButton resposta;                                                             // Cria uma variável para armazenar a resposta do usuário
        resposta = QMessageBox::question(this, "Desfazer Mudanças", 
        "Tem certeza que deseja desfazer as mudanças?", QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {                                                               // Verifica se o usuário confirmou a ação
            on_tw_estoque_cellClicked(row, 0);                                                            // Chama a função que lida com o clique na célula da tabela
        }
    } else {                                                                                              // Caso nenhuma linha esteja selecionada
        qDebug() << "Nenhuma linha selecionada.";                                                         // Loga a mensagem no console de debug
    }
}  

void MainWindow::on_btnAtualizar_clicked()                                                                // Função chamada quando o botão "Atualizar" é clicado
{                                                              
    int row = ui->tw_estoque->currentRow();                                                               // Obtém a linha selecionada na tabela de estoque

    if(row != -1) {                                                                                       // Verifica se alguma linha está selecionada

        int id = ui->tw_estoque->item(row, 0)->text().toInt();                                            // Obtém o ID do produto na linha selecionada

        QString produto = ui->lineEditProduto->text();                                                    // Obtém o texto do campo de produto
        int quantidade = ui->spinQuantidade->value();                                                     // Obtém o valor do spin box de quantidade
        double valor_compra = ui->doubleSpinCompra->value();                                              // Obtém o valor do double spin box de compra
        double valor_venda = ui->doubleSpinVenda->value();                                                // Obtém o valor do double spin box de venda
        QString fornecedor = ui->lineEditFornecedor->text();                                              // Obtém o texto do campo de fornecedor

        QSqlQuery query;                                                                                  // Cria um objeto para executar a query SQL

        query.prepare("UPDATE tb_estoque SET produto = :produto, quantidade = :quantidade, valor_compra = :valor_compra, "
        "valor_venda = :valor_venda, fornecedor = :fornecedor WHERE id = :id");                           // Prepara a query para atualizar o produto com o ID especificado
        query.bindValue(":produto", produto);                                                             // Vincula o valor do produto à query
        query.bindValue(":quantidade", quantidade);                                                       // Vincula o valor da quantidade à query
        query.bindValue(":valor_compra", valor_compra);                                                   // Vincula o valor de compra à query
        query.bindValue(":valor_venda", valor_venda);                                                     // Vincula o valor de venda à query
        query.bindValue(":fornecedor", fornecedor);                                                       // Vincula o valor do fornecedor à query
        query.bindValue(":id", id);                                                                       // Vincula o valor do ID à query

        if (query.exec()) {                                                                               // Executa a query e verifica se foi bem-sucedida

            on_lineEditEstoque_textChanged("");                                                           // Atualiza a tabela de estoque

            ui->tw_estoque->selectRow(row);                                                               // Seleciona a linha atual na tabela de estoque

        } else {                                                                                          // Caso a query falhe
            qDebug() << "Erro ao atualizar o produto:" << query.lastError().text();                       // Loga o erro no console de debug
        }

    } else {                                                                                              // Caso nenhuma linha esteja selecionada
        qDebug() << "Nenhuma linha selecionada.";                                                         // Loga a mensagem no console de debug
    }
}

void MainWindow::on_btnAdicionar_clicked()                                                                // Função chamada quando o botão "Adicionar" é clicado
{                                                              
    QString produto = ui->lineEditProdutoAdd->text();                                                     // Obtém o texto do campo de produto
    QString fornecedor = ui->lineEditFornecedorAdd->text();                                               // Obtém o texto do campo de fornecedor

    QSqlQuery query;                                                                                      // Cria um objeto para executar a query SQL

    query.prepare("INSERT INTO tb_estoque (produto, fornecedor) VALUES (:produto, :fornecedor)");         // Prepara a query para inserir um novo produto no estoque
    query.bindValue(":produto", produto);                                                                 // Vincula o valor do produto à query
    query.bindValue(":fornecedor", fornecedor);                                                           // Vincula o valor do fornecedor à query

    if (query.exec()) {                                                                                   // Executa a query e verifica se foi bem-sucedida
        QMessageBox::information(this, " ", "Produto adicionado ao estoque com sucesso.");                // Exibe uma mensagem de sucesso

        ui->lineEditProdutoAdd->clear();                                                                  // Limpa o campo de texto do produto
        ui->lineEditFornecedorAdd->clear();                                                               // Limpa o campo de texto do fornecedor

        on_lineEditEstoque_textChanged("");                                                               // Atualiza a tabela de estoque

    } else {                                                                                              // Caso a query falhe
        qDebug() << "Erro ao executar a query:" << query.lastError().text();                              // Loga o erro no console de debug
        QMessageBox::warning(this, " ", "Erro ao adicionar o produto.");                                  // Exibe uma mensagem de erro
    }

}

void MainWindow::on_btnApagar_clicked()                                                                   // Função chamada quando o botão "Apagar" é clicado
{                                                                 
    int row = ui->tw_estoque->currentRow();                                                               // Obtém a linha selecionada na tabela de estoque

    if(row != -1) {                                                                                       // Verifica se alguma linha está selecionada

        int id = ui->tw_estoque->item(row, 0)->text().toInt();                                            // Obtém o ID do produto na linha selecionada

        QMessageBox::StandardButton resposta;                                                             // Cria uma variável para armazenar a resposta do usuário
        resposta = QMessageBox::question(this, "Apagar Produto", 
        "Tem certeza que deseja apagar o produto?", QMessageBox::Yes | QMessageBox::No);

        if (resposta == QMessageBox::Yes) {                                                               // Verifica se o usuário confirmou a exclusão

            QSqlQuery query;                                                                              // Cria um objeto para executar a query SQL

            query.prepare("DELETE FROM tb_estoque WHERE id = :id");                                       // Prepara a query para deletar o produto com o ID especificado
            query.bindValue(":id", id);                                                                   // Vincula o valor do ID à query

            if (query.exec()) {                                                                           // Executa a query e verifica se foi bem-sucedida
                QMessageBox::information(this, " ", "Produto excluído com sucesso.");                      // Exibe uma mensagem de sucesso
                ui->tw_estoque->removeRow(row);                                                           // Remove a linha da tabela de estoque

                ui->lineEditProduto->setText("");                                                         // Limpa o campo de texto do produto
                ui->spinQuantidade->setValue(0);                                                          // Reseta o valor do spin box de quantidade
                ui->doubleSpinCompra->setValue(0);                                                        // Reseta o valor do double spin box de compra
                ui->doubleSpinVenda->setValue(0);                                                         // Reseta o valor do double spin box de venda
                ui->lineEditFornecedor->setText("");                                                      // Limpa o campo de texto do fornecedor

            } else {                                                                                      // Caso a query falhe
                QMessageBox::warning(this, " ", "Erro ao excluir o produto.");                             // Exibe uma mensagem de erro
                qDebug() << "Erro ao executar a query:" << query.lastError().text();                      // Loga o erro no console de debug
            }

        }

    } else {                                                                                              // Caso nenhuma linha esteja selecionada
        qDebug() << "Nenhuma linha selecionada.";                                                         // Loga a mensagem no console de debug
    }
}

// FIM DA PÁGINA FORNCEDORES


///////////////////////////////////////////////////
