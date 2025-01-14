/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame_2;
    QLabel *label_3;
    QFrame *line;
    QLabel *label_4;
    QLabel *label_5;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QCommandLinkButton *btnAtendimento;
    QCommandLinkButton *btnPacientes;
    QCommandLinkButton *btnProfissionais;
    QCommandLinkButton *btnFornecedores;
    QCommandLinkButton *btnRelatorios;
    QCommandLinkButton *btnAgenda;
    QTabWidget *paginas;
    QWidget *Agenda;
    QLabel *label_6;
    QWidget *Atendimento;
    QLabel *label_7;
    QWidget *Pacientes;
    QLabel *label_8;
    QWidget *Profissionais;
    QLabel *label_9;
    QWidget *Relatorios;
    QLabel *label_10;
    QWidget *Fornecedores;
    QLabel *label_11;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1280, 720));
        MainWindow->setMaximumSize(QSize(1280, 720));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setEnabled(true);
        frame->setGeometry(QRect(0, 0, 1280, 70));
        frame->setAutoFillBackground(false);
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(109, 176, 236)"));
        frame->setFrameShape(QFrame::Shape::NoFrame);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(85, 17, 287, 36));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Arial\";\n"
"color: rgb(255, 255, 255);"));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(952, 17, 287, 36));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("font: 16pt \"Arial\";\n"
"color: rgb(255, 255, 255);"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setEnabled(true);
        frame_2->setGeometry(QRect(0, 70, 170, 650));
        frame_2->setAutoFillBackground(false);
        frame_2->setStyleSheet(QString::fromUtf8("background-color:rgb(109, 176, 236)"));
        frame_2->setFrameShape(QFrame::Shape::NoFrame);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(13, 37, 107, 23));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(10);
        font1.setBold(true);
        label_3->setFont(font1);
        line = new QFrame(frame_2);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 64, 150, 5));
        line->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(13, 117, 107, 23));
        label_4->setFont(font1);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(13, 189, 107, 23));
        label_5->setFont(font1);
        line_2 = new QFrame(frame_2);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(10, 146, 150, 5));
        line_2->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(frame_2);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(10, 219, 150, 5));
        line_3->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        line_4 = new QFrame(frame_2);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(36, 260, 124, 5));
        line_4->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        line_5 = new QFrame(frame_2);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(36, 300, 124, 5));
        line_5->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);
        line_6 = new QFrame(frame_2);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(36, 340, 124, 5));
        line_6->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);
        btnAtendimento = new QCommandLinkButton(frame_2);
        btnAtendimento->setObjectName("btnAtendimento");
        btnAtendimento->setGeometry(QRect(30, 150, 141, 41));
        btnAtendimento->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnAtendimento->setText(QString::fromUtf8("Atendimento"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Survey.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAtendimento->setIcon(icon);
        btnPacientes = new QCommandLinkButton(frame_2);
        btnPacientes->setObjectName("btnPacientes");
        btnPacientes->setGeometry(QRect(30, 220, 141, 41));
        btnPacientes->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnPacientes->setText(QString::fromUtf8("Pacientes"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/People.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnPacientes->setIcon(icon1);
        btnProfissionais = new QCommandLinkButton(frame_2);
        btnProfissionais->setObjectName("btnProfissionais");
        btnProfissionais->setGeometry(QRect(30, 260, 141, 41));
        btnProfissionais->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnProfissionais->setText(QString::fromUtf8("Profissionais"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Medical Doctor.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnProfissionais->setIcon(icon2);
        btnFornecedores = new QCommandLinkButton(frame_2);
        btnFornecedores->setObjectName("btnFornecedores");
        btnFornecedores->setGeometry(QRect(30, 340, 141, 41));
        btnFornecedores->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnFornecedores->setText(QString::fromUtf8("Fornecedores"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/City Buildings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnFornecedores->setIcon(icon3);
        btnRelatorios = new QCommandLinkButton(frame_2);
        btnRelatorios->setObjectName("btnRelatorios");
        btnRelatorios->setGeometry(QRect(30, 300, 141, 41));
        btnRelatorios->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnRelatorios->setText(QString::fromUtf8("Relat\303\263rios"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/Brief.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnRelatorios->setIcon(icon4);
        btnAgenda = new QCommandLinkButton(frame_2);
        btnAgenda->setObjectName("btnAgenda");
        btnAgenda->setGeometry(QRect(30, 70, 141, 41));
        btnAgenda->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        btnAgenda->setText(QString::fromUtf8("Agenda"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/Tear-Off Calendar.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAgenda->setIcon(icon5);
        btnAgenda->setCheckable(false);
        btnAgenda->setAutoRepeat(false);
        paginas = new QTabWidget(centralwidget);
        paginas->setObjectName("paginas");
        paginas->setGeometry(QRect(170, 30, 1111, 671));
        Agenda = new QWidget();
        Agenda->setObjectName("Agenda");
        label_6 = new QLabel(Agenda);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 50, 63, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        paginas->addTab(Agenda, QString());
        Atendimento = new QWidget();
        Atendimento->setObjectName("Atendimento");
        label_7 = new QLabel(Atendimento);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 50, 111, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        paginas->addTab(Atendimento, QString());
        Pacientes = new QWidget();
        Pacientes->setObjectName("Pacientes");
        label_8 = new QLabel(Pacientes);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(40, 50, 111, 20));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        paginas->addTab(Pacientes, QString());
        Profissionais = new QWidget();
        Profissionais->setObjectName("Profissionais");
        label_9 = new QLabel(Profissionais);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(50, 50, 111, 20));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        paginas->addTab(Profissionais, QString());
        Relatorios = new QWidget();
        Relatorios->setObjectName("Relatorios");
        label_10 = new QLabel(Relatorios);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(50, 50, 111, 20));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        paginas->addTab(Relatorios, QString());
        Fornecedores = new QWidget();
        Fornecedores->setObjectName("Fornecedores");
        label_11 = new QLabel(Fornecedores);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(60, 50, 111, 20));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        paginas->addTab(Fornecedores, QString());
        MainWindow->setCentralWidget(centralwidget);
        paginas->raise();
        frame_2->raise();
        frame->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        paginas->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:700; color:#000000;\">NOME_SOFTWARE</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:700; color:#000000;\">NOME_CL\303\215NICA</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; color:#000000;\">Cronograma</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; color:#000000;\">Prontu\303\241rio</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; color:#000000;\">Gest\303\243o</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "AGENDA", nullptr));
        paginas->setTabText(paginas->indexOf(Agenda), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "ATENDIMENTO", nullptr));
        paginas->setTabText(paginas->indexOf(Atendimento), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "PACIENTES", nullptr));
        paginas->setTabText(paginas->indexOf(Pacientes), QCoreApplication::translate("MainWindow", "Page", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "PROFISSIONAIS", nullptr));
        paginas->setTabText(paginas->indexOf(Profissionais), QCoreApplication::translate("MainWindow", "Page", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "RELAT\303\223RIOS", nullptr));
        paginas->setTabText(paginas->indexOf(Relatorios), QCoreApplication::translate("MainWindow", "Page", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "FORNECEDORES", nullptr));
        paginas->setTabText(paginas->indexOf(Fornecedores), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
