#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QTabWidget>
#include <QCommandLinkButton>

#include "cadastropacientes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAgenda_clicked();
    void on_btnAtendimento_clicked();
    void on_btnPacientes_clicked();
    void on_btnProfissionais_clicked();
    void on_btnFornecedores_clicked();
    void on_btnRelatorios_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
