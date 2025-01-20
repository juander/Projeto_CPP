#ifndef JANELA_ENTRAR_H
#define JANELA_ENTRAR_H

#include <QDialog>

namespace Ui {
class janela_entrar;
}

class janela_entrar : public QDialog
{
    Q_OBJECT

public:
    explicit janela_entrar(QWidget *parent = nullptr);
    ~janela_entrar();

private:
    Ui::janela_entrar *ui;
};

#endif // JANELA_ENTRAR_H
