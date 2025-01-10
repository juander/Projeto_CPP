#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Pessoa {
protected:
    std::string nome;
    int idade;

public:
    Pessoa(std::string n, int i);
    virtual ~Pessoa() = default;
    std::string getNome() const;
    int getIdade() const;
};

class Paciente : public Pessoa {
    std::string diagnostico;

public:
    Paciente(std::string n, int i, std::string d);
    std::string getDiagnostico() const;
    std::string getInfo() const;
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
    std::vector<Paciente> pacientes;
};

#endif // MAINWINDOW_H
