#ifndef CADASTROSESSAO_H
#define CADASTROSESSAO_H

#include <QDialog>

namespace Ui {
class cadastroSessao;
}

class cadastroSessao : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroSessao(QWidget *parent = nullptr);
    ~cadastroSessao();

private:
    Ui::cadastroSessao *ui;
};

#endif // CADASTROSESSAO_H
