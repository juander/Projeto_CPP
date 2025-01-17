/********************************************************************************
** Form generated from reading UI file 'edicaocolaboradores.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDICAOCOLABORADORES_H
#define UI_EDICAOCOLABORADORES_H

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

class Ui_edicaoColaboradores
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
    QLineEdit *txtcargo;
    QLabel *label_3;
    QLineEdit *txtcontato;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *txtemail;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *editar;
    QPushButton *cancelarEdit;

    void setupUi(QDialog *edicaoColaboradores)
    {
        if (edicaoColaboradores->objectName().isEmpty())
            edicaoColaboradores->setObjectName("edicaoColaboradores");
        edicaoColaboradores->resize(413, 249);
        verticalLayout_2 = new QVBoxLayout(edicaoColaboradores);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_7 = new QLabel(edicaoColaboradores);
        label_7->setObjectName("label_7");

        horizontalLayout_10->addWidget(label_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

        label_8 = new QLabel(edicaoColaboradores);
        label_8->setObjectName("label_8");

        horizontalLayout_10->addWidget(label_8);

        txtID = new QLabel(edicaoColaboradores);
        txtID->setObjectName("txtID");

        horizontalLayout_10->addWidget(txtID);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(edicaoColaboradores);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        txtnome = new QLineEdit(edicaoColaboradores);
        txtnome->setObjectName("txtnome");

        horizontalLayout->addWidget(txtnome);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(edicaoColaboradores);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        txtCpf = new QLineEdit(edicaoColaboradores);
        txtCpf->setObjectName("txtCpf");

        horizontalLayout_2->addWidget(txtCpf);

        label_2 = new QLabel(edicaoColaboradores);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        txtData = new QDateEdit(edicaoColaboradores);
        txtData->setObjectName("txtData");

        horizontalLayout_2->addWidget(txtData);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(edicaoColaboradores);
        label_6->setObjectName("label_6");

        horizontalLayout_4->addWidget(label_6);

        txtcargo = new QLineEdit(edicaoColaboradores);
        txtcargo->setObjectName("txtcargo");

        horizontalLayout_4->addWidget(txtcargo);

        label_3 = new QLabel(edicaoColaboradores);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        txtcontato = new QLineEdit(edicaoColaboradores);
        txtcontato->setObjectName("txtcontato");

        horizontalLayout_4->addWidget(txtcontato);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(edicaoColaboradores);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        txtemail = new QLineEdit(edicaoColaboradores);
        txtemail->setObjectName("txtemail");

        horizontalLayout_6->addWidget(txtemail);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        editar = new QPushButton(edicaoColaboradores);
        editar->setObjectName("editar");

        horizontalLayout_7->addWidget(editar);

        cancelarEdit = new QPushButton(edicaoColaboradores);
        cancelarEdit->setObjectName("cancelarEdit");

        horizontalLayout_7->addWidget(cancelarEdit);


        verticalLayout->addLayout(horizontalLayout_7);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(edicaoColaboradores);

        QMetaObject::connectSlotsByName(edicaoColaboradores);
    } // setupUi

    void retranslateUi(QDialog *edicaoColaboradores)
    {
        edicaoColaboradores->setWindowTitle(QCoreApplication::translate("edicaoColaboradores", "Dialog", nullptr));
        label_7->setText(QCoreApplication::translate("edicaoColaboradores", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Editar Colaborador</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("edicaoColaboradores", "ID:", nullptr));
        txtID->setText(QCoreApplication::translate("edicaoColaboradores", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("edicaoColaboradores", "Nome:", nullptr));
        label_5->setText(QCoreApplication::translate("edicaoColaboradores", "CPF:", nullptr));
        label_2->setText(QCoreApplication::translate("edicaoColaboradores", "Nascimento:", nullptr));
        label_6->setText(QCoreApplication::translate("edicaoColaboradores", "Cargo", nullptr));
        label_3->setText(QCoreApplication::translate("edicaoColaboradores", "N\302\272Celular:", nullptr));
        label_4->setText(QCoreApplication::translate("edicaoColaboradores", "E-mail:", nullptr));
        editar->setText(QCoreApplication::translate("edicaoColaboradores", "Editar", nullptr));
        cancelarEdit->setText(QCoreApplication::translate("edicaoColaboradores", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edicaoColaboradores: public Ui_edicaoColaboradores {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDICAOCOLABORADORES_H
