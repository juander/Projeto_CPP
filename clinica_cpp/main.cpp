#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);             // Inicializa a aplicação Qt
    MainWindow janelaPrincipal;               // Cria a janela principal

    janelaPrincipal.setPaletaCor(app);        // Setando o tema claro para a aplicação usando método implementado

    janelaPrincipal.showMaximized();          // Exibe a janela principal
    return app.exec();                        // Executa o loop de eventos da aplicação
}
