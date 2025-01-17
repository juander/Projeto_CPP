/********************************************************************************
** Form generated from reading UI file 'cadastrocolaboradores.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADASTROCOLABORADORES_H
#define UI_CADASTROCOLABORADORES_H

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

class Ui_cadastroColaboradores
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
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *txtcargo;
    QLabel *label_7;
    QLineEdit *txtcontato;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *txtemail;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnCadastrarCol;
    QPushButton *btnCancelarCol;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *cadastroColaboradores)
    {
        if (cadastroColaboradores->objectName().isEmpty())
            cadastroColaboradores->setObjectName("cadastroColaboradores");
        cadastroColaboradores->resize(403, 247);
        verticalLayout_2 = new QVBoxLayout(cadastroColaboradores);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(cadastroColaboradores);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(cadastroColaboradores);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        txtnome = new QLineEdit(cadastroColaboradores);
        txtnome->setObjectName("txtnome");

        horizontalLayout->addWidget(txtnome);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_8 = new QLabel(cadastroColaboradores);
        label_8->setObjectName("label_8");

        horizontalLayout_2->addWidget(label_8);

        txtCpf = new QLineEdit(cadastroColaboradores);
        txtCpf->setObjectName("txtCpf");

        horizontalLayout_2->addWidget(txtCpf);

        label_5 = new QLabel(cadastroColaboradores);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        txtData = new QDateEdit(cadastroColaboradores);
        txtData->setObjectName("txtData");

        horizontalLayout_2->addWidget(txtData);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(cadastroColaboradores);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        txtcargo = new QLineEdit(cadastroColaboradores);
        txtcargo->setObjectName("txtcargo");

        horizontalLayout_3->addWidget(txtcargo);

        label_7 = new QLabel(cadastroColaboradores);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        txtcontato = new QLineEdit(cadastroColaboradores);
        txtcontato->setObjectName("txtcontato");

        horizontalLayout_3->addWidget(txtcontato);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(cadastroColaboradores);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        txtemail = new QLineEdit(cadastroColaboradores);
        txtemail->setObjectName("txtemail");

        horizontalLayout_4->addWidget(txtemail);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btnCadastrarCol = new QPushButton(cadastroColaboradores);
        btnCadastrarCol->setObjectName("btnCadastrarCol");

        horizontalLayout_5->addWidget(btnCadastrarCol);

        btnCancelarCol = new QPushButton(cadastroColaboradores);
        btnCancelarCol->setObjectName("btnCancelarCol");

        horizontalLayout_5->addWidget(btnCancelarCol);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(cadastroColaboradores);

        QMetaObject::connectSlotsByName(cadastroColaboradores);
    } // setupUi

    void retranslateUi(QDialog *cadastroColaboradores)
    {
        cadastroColaboradores->setWindowTitle(QCoreApplication::translate("cadastroColaboradores", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("cadastroColaboradores", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:700;\">Cadastro de Colaborador</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("cadastroColaboradores", "Nome:", nullptr));
        label_8->setText(QCoreApplication::translate("cadastroColaboradores", "CPF:", nullptr));
        label_5->setText(QCoreApplication::translate("cadastroColaboradores", "Nascimento:", nullptr));
        label_2->setText(QCoreApplication::translate("cadastroColaboradores", "Cargo", nullptr));
        label_7->setText(QCoreApplication::translate("cadastroColaboradores", "N\302\272Celular:", nullptr));
        label_3->setText(QCoreApplication::translate("cadastroColaboradores", "E-Mail:", nullptr));
        btnCadastrarCol->setText(QCoreApplication::translate("cadastroColaboradores", "Cadastrar", nullptr));
        btnCancelarCol->setText(QCoreApplication::translate("cadastroColaboradores", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cadastroColaboradores: public Ui_cadastroColaboradores {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADASTROCOLABORADORES_H
