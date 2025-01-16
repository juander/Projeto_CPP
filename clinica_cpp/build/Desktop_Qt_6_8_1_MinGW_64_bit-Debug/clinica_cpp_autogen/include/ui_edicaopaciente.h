/********************************************************************************
** Form generated from reading UI file 'edicaopaciente.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDICAOPACIENTE_H
#define UI_EDICAOPACIENTE_H

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

class Ui_edicaopaciente
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QLabel *label_8;
    QLabel *txtID;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtnome;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *txtCpf;
    QLabel *label_2;
    QDateEdit *txtData;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *txtconvenio;
    QLabel *label_3;
    QLineEdit *txtcontato;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *txtemail;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *editar;
    QPushButton *cancelarEdit;

    void setupUi(QDialog *edicaopaciente)
    {
        if (edicaopaciente->objectName().isEmpty())
            edicaopaciente->setObjectName("edicaopaciente");
        edicaopaciente->resize(495, 286);
        verticalLayout_2 = new QVBoxLayout(edicaopaciente);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_7 = new QLabel(edicaopaciente);
        label_7->setObjectName("label_7");

        horizontalLayout_10->addWidget(label_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

        label_8 = new QLabel(edicaopaciente);
        label_8->setObjectName("label_8");

        horizontalLayout_10->addWidget(label_8);

        txtID = new QLabel(edicaopaciente);
        txtID->setObjectName("txtID");

        horizontalLayout_10->addWidget(txtID);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(edicaopaciente);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        txtnome = new QLineEdit(edicaopaciente);
        txtnome->setObjectName("txtnome");

        horizontalLayout->addWidget(txtnome);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(edicaopaciente);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        txtCpf = new QLineEdit(edicaopaciente);
        txtCpf->setObjectName("txtCpf");

        horizontalLayout_2->addWidget(txtCpf);

        label_2 = new QLabel(edicaopaciente);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        txtData = new QDateEdit(edicaopaciente);
        txtData->setObjectName("txtData");

        horizontalLayout_2->addWidget(txtData);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(edicaopaciente);
        label_6->setObjectName("label_6");

        horizontalLayout_4->addWidget(label_6);

        txtconvenio = new QLineEdit(edicaopaciente);
        txtconvenio->setObjectName("txtconvenio");

        horizontalLayout_4->addWidget(txtconvenio);

        label_3 = new QLabel(edicaopaciente);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        txtcontato = new QLineEdit(edicaopaciente);
        txtcontato->setObjectName("txtcontato");

        horizontalLayout_4->addWidget(txtcontato);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(edicaopaciente);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        txtemail = new QLineEdit(edicaopaciente);
        txtemail->setObjectName("txtemail");

        horizontalLayout_6->addWidget(txtemail);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        editar = new QPushButton(edicaopaciente);
        editar->setObjectName("editar");

        horizontalLayout_7->addWidget(editar);

        cancelarEdit = new QPushButton(edicaopaciente);
        cancelarEdit->setObjectName("cancelarEdit");

        horizontalLayout_7->addWidget(cancelarEdit);


        verticalLayout->addLayout(horizontalLayout_7);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(edicaopaciente);

        QMetaObject::connectSlotsByName(edicaopaciente);
    } // setupUi

    void retranslateUi(QDialog *edicaopaciente)
    {
        edicaopaciente->setWindowTitle(QCoreApplication::translate("edicaopaciente", "Editar", nullptr));
        label_7->setText(QCoreApplication::translate("edicaopaciente", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Editar Paciente</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("edicaopaciente", "ID:", nullptr));
        txtID->setText(QCoreApplication::translate("edicaopaciente", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("edicaopaciente", "Nome:", nullptr));
        label_5->setText(QCoreApplication::translate("edicaopaciente", "CPF:", nullptr));
        label_2->setText(QCoreApplication::translate("edicaopaciente", "Nascimento:", nullptr));
        label_6->setText(QCoreApplication::translate("edicaopaciente", "Conv\303\252nio/Plano", nullptr));
        label_3->setText(QCoreApplication::translate("edicaopaciente", "N\302\272Celular:", nullptr));
        label_4->setText(QCoreApplication::translate("edicaopaciente", "E-mail:", nullptr));
        editar->setText(QCoreApplication::translate("edicaopaciente", "Editar", nullptr));
        cancelarEdit->setText(QCoreApplication::translate("edicaopaciente", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edicaopaciente: public Ui_edicaopaciente {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDICAOPACIENTE_H
