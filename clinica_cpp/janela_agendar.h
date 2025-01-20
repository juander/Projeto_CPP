#ifndef JANELA_AGENDAR_H
#define JANELA_AGENDAR_H

#include <QDialog>

namespace Ui {
class janela_agendar;
}

class janela_agendar : public QDialog
{
    Q_OBJECT

public:
    explicit janela_agendar(QWidget *parent = nullptr);
    ~janela_agendar();

private:
    Ui::janela_agendar *ui;
};

#endif // JANELA_AGENDAR_H
