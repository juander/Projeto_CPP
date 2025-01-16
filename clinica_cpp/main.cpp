#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Inicializa a aplicação Qt
    MainWindow w; // Cria a janela principal
    w.show(); // Exibe a janela principal
    return a.exec(); // Executa o loop de eventos da aplicação
}

// Vê se foi
