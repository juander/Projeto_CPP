/********************************************************************************
** Form generated from reading UI file 'cadastropacientes.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADASTROPACIENTES_H
#define UI_CADASTROPACIENTES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_cadastroPacientes
{
public:

    void setupUi(QDialog *cadastroPacientes)
    {
        if (cadastroPacientes->objectName().isEmpty())
            cadastroPacientes->setObjectName("cadastroPacientes");
        cadastroPacientes->resize(400, 300);

        retranslateUi(cadastroPacientes);

        QMetaObject::connectSlotsByName(cadastroPacientes);
    } // setupUi

    void retranslateUi(QDialog *cadastroPacientes)
    {
        cadastroPacientes->setWindowTitle(QCoreApplication::translate("cadastroPacientes", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cadastroPacientes: public Ui_cadastroPacientes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADASTROPACIENTES_H
