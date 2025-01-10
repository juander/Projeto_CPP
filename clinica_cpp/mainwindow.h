#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Pessoa {
protected:
    string nome;
    int idade;

public:
    Pessoa(string n, int i);
    virtual ~Pessoa() = default;
    string getNome() const;
    int getIdade() const;
};

class Paciente : public Pessoa {
    string diagnostico;

public:
    Paciente(string n, int i, string d);
    string getDiagnostico() const;
    string getInfo() const;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCadastrar_clicked();
    void on_btnExibir_clicked();
private:
    Ui::MainWindow *ui;
    vector<Paciente> pacientes;
};

#endif // MAINWINDOW_H
