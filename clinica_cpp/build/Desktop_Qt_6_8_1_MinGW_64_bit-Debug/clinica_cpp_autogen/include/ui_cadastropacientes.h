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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_cadastroPacientes
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtnome;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *txtCpf;
    QLabel *label_5;
    QDateEdit *txtData;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLineEdit *txtDiagn;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *txtconvenio;
    QLabel *label_7;
    QLineEdit *txtcontato;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *txtemail;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnCadastrar;
    QPushButton *btnCancelar;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *cadastroPacientes)
    {
        if (cadastroPacientes->objectName().isEmpty())
            cadastroPacientes->setObjectName("cadastroPacientes");
        cadastroPacientes->resize(479, 284);
        verticalLayout_2 = new QVBoxLayout(cadastroPacientes);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(cadastroPacientes);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(cadastroPacientes);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        txtnome = new QLineEdit(cadastroPacientes);
        txtnome->setObjectName("txtnome");

        horizontalLayout->addWidget(txtnome);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_8 = new QLabel(cadastroPacientes);
        label_8->setObjectName("label_8");

        horizontalLayout_2->addWidget(label_8);

        txtCpf = new QLineEdit(cadastroPacientes);
        txtCpf->setObjectName("txtCpf");

        horizontalLayout_2->addWidget(txtCpf);

        label_5 = new QLabel(cadastroPacientes);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        txtData = new QDateEdit(cadastroPacientes);
        txtData->setObjectName("txtData");

        horizontalLayout_2->addWidget(txtData);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_9 = new QLabel(cadastroPacientes);
        label_9->setObjectName("label_9");

        horizontalLayout_7->addWidget(label_9);

        txtDiagn = new QLineEdit(cadastroPacientes);
        txtDiagn->setObjectName("txtDiagn");

        horizontalLayout_7->addWidget(txtDiagn);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(cadastroPacientes);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        txtconvenio = new QLineEdit(cadastroPacientes);
        txtconvenio->setObjectName("txtconvenio");

        horizontalLayout_3->addWidget(txtconvenio);

        label_7 = new QLabel(cadastroPacientes);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        txtcontato = new QLineEdit(cadastroPacientes);
        txtcontato->setObjectName("txtcontato");

        horizontalLayout_3->addWidget(txtcontato);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(cadastroPacientes);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        txtemail = new QLineEdit(cadastroPacientes);
        txtemail->setObjectName("txtemail");

        horizontalLayout_4->addWidget(txtemail);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btnCadastrar = new QPushButton(cadastroPacientes);
        btnCadastrar->setObjectName("btnCadastrar");

        horizontalLayout_5->addWidget(btnCadastrar);

        btnCancelar = new QPushButton(cadastroPacientes);
        btnCancelar->setObjectName("btnCancelar");

        horizontalLayout_5->addWidget(btnCancelar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(cadastroPacientes);

        QMetaObject::connectSlotsByName(cadastroPacientes);
    } // setupUi

    void retranslateUi(QDialog *cadastroPacientes)
    {
        cadastroPacientes->setWindowTitle(QCoreApplication::translate("cadastroPacientes", "Cadastro", nullptr));
        label_6->setText(QCoreApplication::translate("cadastroPacientes", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:700;\">Cadastro de Paciente</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("cadastroPacientes", "Nome:", nullptr));
        label_8->setText(QCoreApplication::translate("cadastroPacientes", "CPF:", nullptr));
        label_5->setText(QCoreApplication::translate("cadastroPacientes", "Nascimento:", nullptr));
        label_9->setText(QCoreApplication::translate("cadastroPacientes", "Diagn\303\263stico:", nullptr));
        label_2->setText(QCoreApplication::translate("cadastroPacientes", "Conv\303\252nio / Plano:", nullptr));
        label_7->setText(QCoreApplication::translate("cadastroPacientes", "N\302\272Celular:", nullptr));
        label_3->setText(QCoreApplication::translate("cadastroPacientes", "E-Mail:", nullptr));
        btnCadastrar->setText(QCoreApplication::translate("cadastroPacientes", "Cadastrar", nullptr));
        btnCancelar->setText(QCoreApplication::translate("cadastroPacientes", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cadastroPacientes: public Ui_cadastroPacientes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADASTROPACIENTES_H
