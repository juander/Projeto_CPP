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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cadastroPacientes
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
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
        cadastroPacientes->resize(482, 296);
        layoutWidget = new QWidget(cadastroPacientes);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 457, 272));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        txtnome = new QLineEdit(layoutWidget);
        txtnome->setObjectName("txtnome");

        horizontalLayout->addWidget(txtnome);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName("label_8");

        horizontalLayout_2->addWidget(label_8);

        txtCpf = new QLineEdit(layoutWidget);
        txtCpf->setObjectName("txtCpf");

        horizontalLayout_2->addWidget(txtCpf);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        txtData = new QDateEdit(layoutWidget);
        txtData->setObjectName("txtData");

        horizontalLayout_2->addWidget(txtData);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        txtconvenio = new QLineEdit(layoutWidget);
        txtconvenio->setObjectName("txtconvenio");

        horizontalLayout_3->addWidget(txtconvenio);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        txtcontato = new QLineEdit(layoutWidget);
        txtcontato->setObjectName("txtcontato");

        horizontalLayout_3->addWidget(txtcontato);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        txtemail = new QLineEdit(layoutWidget);
        txtemail->setObjectName("txtemail");

        horizontalLayout_4->addWidget(txtemail);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btnCadastrar = new QPushButton(layoutWidget);
        btnCadastrar->setObjectName("btnCadastrar");

        horizontalLayout_5->addWidget(btnCadastrar);

        btnCancelar = new QPushButton(layoutWidget);
        btnCancelar->setObjectName("btnCancelar");

        horizontalLayout_5->addWidget(btnCancelar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(cadastroPacientes);

        QMetaObject::connectSlotsByName(cadastroPacientes);
    } // setupUi

    void retranslateUi(QDialog *cadastroPacientes)
    {
        cadastroPacientes->setWindowTitle(QCoreApplication::translate("cadastroPacientes", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("cadastroPacientes", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Cadastro de Paciente</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("cadastroPacientes", "Nome:", nullptr));
        label_8->setText(QCoreApplication::translate("cadastroPacientes", "CPF:", nullptr));
        label_5->setText(QCoreApplication::translate("cadastroPacientes", "Nascimento:", nullptr));
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
