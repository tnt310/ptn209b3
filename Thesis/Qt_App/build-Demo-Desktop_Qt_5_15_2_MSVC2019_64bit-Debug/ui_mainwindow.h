/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_8;
    QComboBox *DATABIT;
    QFrame *line_2;
    QComboBox *BAUD;
    QLabel *label_2;
    QLabel *label;
    QPushButton *OPENBUTTON;
    QComboBox *STOPBITS;
    QFrame *line;
    QLabel *label_12;
    QPushButton *CLOSEBUTTON;
    QComboBox *PARITY;
    QLabel *label_10;
    QLabel *label_5;
    QPushButton *UPDATE;
    QComboBox *COM;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_6;
    QLabel *label_3;
    QPushButton *bt_refresh;
    QTextEdit *testing;
    QTextEdit *testing_2;
    QTextEdit *IP;
    QTextEdit *NETMASK;
    QTextEdit *GATEWAY;
    QLabel *label_13;
    QLabel *label_14;
    QComboBox *BAUD_2;
    QLabel *label_15;
    QComboBox *BAUD_3;
    QLabel *label_16;
    QComboBox *DATABIT_2;
    QLabel *label_17;
    QComboBox *STOPBITS_2;
    QLabel *label_18;
    QComboBox *PARITY_2;
    QPushButton *UPDATE_2;
    QLabel *label_19;
    QTextEdit *testing_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1032, 527);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(360, 40, 31, 21));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(340, 10, 261, 31));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_7->setFont(font1);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 110, 71, 21));
        label_8->setFont(font);
        DATABIT = new QComboBox(centralwidget);
        DATABIT->addItem(QString());
        DATABIT->addItem(QString());
        DATABIT->setObjectName(QString::fromUtf8("DATABIT"));
        DATABIT->setGeometry(QRect(100, 110, 91, 21));
        QFont font2;
        font2.setPointSize(9);
        DATABIT->setFont(font2);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(600, 10, 16, 431));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        BAUD = new QComboBox(centralwidget);
        BAUD->addItem(QString());
        BAUD->addItem(QString());
        BAUD->addItem(QString());
        BAUD->setObjectName(QString::fromUtf8("BAUD"));
        BAUD->setGeometry(QRect(100, 80, 91, 21));
        BAUD->setFont(font2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 41, 21));
        label_2->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 111, 31));
        label->setFont(font1);
        OPENBUTTON = new QPushButton(centralwidget);
        OPENBUTTON->setObjectName(QString::fromUtf8("OPENBUTTON"));
        OPENBUTTON->setGeometry(QRect(110, 270, 93, 31));
        STOPBITS = new QComboBox(centralwidget);
        STOPBITS->addItem(QString());
        STOPBITS->addItem(QString());
        STOPBITS->setObjectName(QString::fromUtf8("STOPBITS"));
        STOPBITS->setGeometry(QRect(100, 140, 91, 21));
        STOPBITS->setFont(font2);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(320, 10, 16, 431));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(340, 330, 41, 21));
        label_12->setFont(font);
        CLOSEBUTTON = new QPushButton(centralwidget);
        CLOSEBUTTON->setObjectName(QString::fromUtf8("CLOSEBUTTON"));
        CLOSEBUTTON->setGeometry(QRect(210, 270, 93, 31));
        PARITY = new QComboBox(centralwidget);
        PARITY->addItem(QString());
        PARITY->addItem(QString());
        PARITY->setObjectName(QString::fromUtf8("PARITY"));
        PARITY->setGeometry(QRect(100, 170, 91, 21));
        PARITY->setFont(font2);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 170, 51, 21));
        label_10->setFont(font);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(340, 80, 61, 21));
        label_5->setFont(font);
        UPDATE = new QPushButton(centralwidget);
        UPDATE->setObjectName(QString::fromUtf8("UPDATE"));
        UPDATE->setGeometry(QRect(420, 270, 101, 31));
        COM = new QComboBox(centralwidget);
        COM->setObjectName(QString::fromUtf8("COM"));
        COM->setGeometry(QRect(100, 50, 91, 21));
        COM->setFont(font2);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 140, 71, 21));
        label_9->setFont(font);
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 330, 41, 21));
        label_11->setFont(font);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(340, 130, 71, 21));
        label_6->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 50, 41, 21));
        label_3->setFont(font);
        bt_refresh = new QPushButton(centralwidget);
        bt_refresh->setObjectName(QString::fromUtf8("bt_refresh"));
        bt_refresh->setGeometry(QRect(10, 270, 91, 31));
        testing = new QTextEdit(centralwidget);
        testing->setObjectName(QString::fromUtf8("testing"));
        testing->setGeometry(QRect(70, 320, 251, 151));
        testing_2 = new QTextEdit(centralwidget);
        testing_2->setObjectName(QString::fromUtf8("testing_2"));
        testing_2->setGeometry(QRect(400, 320, 161, 61));
        IP = new QTextEdit(centralwidget);
        IP->setObjectName(QString::fromUtf8("IP"));
        IP->setGeometry(QRect(420, 40, 151, 31));
        IP->setFont(font2);
        NETMASK = new QTextEdit(centralwidget);
        NETMASK->setObjectName(QString::fromUtf8("NETMASK"));
        NETMASK->setGeometry(QRect(420, 80, 151, 31));
        NETMASK->setFont(font2);
        GATEWAY = new QTextEdit(centralwidget);
        GATEWAY->setObjectName(QString::fromUtf8("GATEWAY"));
        GATEWAY->setGeometry(QRect(420, 130, 151, 31));
        GATEWAY->setFont(font2);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(630, 10, 431, 31));
        label_13->setFont(font1);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(640, 60, 51, 21));
        label_14->setFont(font);
        BAUD_2 = new QComboBox(centralwidget);
        BAUD_2->addItem(QString());
        BAUD_2->addItem(QString());
        BAUD_2->addItem(QString());
        BAUD_2->addItem(QString());
        BAUD_2->setObjectName(QString::fromUtf8("BAUD_2"));
        BAUD_2->setGeometry(QRect(720, 60, 91, 21));
        BAUD_2->setFont(font2);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(640, 100, 41, 21));
        label_15->setFont(font);
        BAUD_3 = new QComboBox(centralwidget);
        BAUD_3->addItem(QString());
        BAUD_3->addItem(QString());
        BAUD_3->addItem(QString());
        BAUD_3->setObjectName(QString::fromUtf8("BAUD_3"));
        BAUD_3->setGeometry(QRect(720, 100, 91, 21));
        BAUD_3->setFont(font2);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(640, 140, 71, 21));
        label_16->setFont(font);
        DATABIT_2 = new QComboBox(centralwidget);
        DATABIT_2->addItem(QString());
        DATABIT_2->addItem(QString());
        DATABIT_2->setObjectName(QString::fromUtf8("DATABIT_2"));
        DATABIT_2->setGeometry(QRect(720, 140, 91, 21));
        DATABIT_2->setFont(font2);
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(640, 180, 71, 21));
        label_17->setFont(font);
        STOPBITS_2 = new QComboBox(centralwidget);
        STOPBITS_2->addItem(QString());
        STOPBITS_2->addItem(QString());
        STOPBITS_2->setObjectName(QString::fromUtf8("STOPBITS_2"));
        STOPBITS_2->setGeometry(QRect(720, 180, 91, 21));
        STOPBITS_2->setFont(font2);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(640, 220, 51, 21));
        label_18->setFont(font);
        PARITY_2 = new QComboBox(centralwidget);
        PARITY_2->addItem(QString());
        PARITY_2->addItem(QString());
        PARITY_2->setObjectName(QString::fromUtf8("PARITY_2"));
        PARITY_2->setGeometry(QRect(720, 220, 91, 21));
        PARITY_2->setFont(font2);
        UPDATE_2 = new QPushButton(centralwidget);
        UPDATE_2->setObjectName(QString::fromUtf8("UPDATE_2"));
        UPDATE_2->setGeometry(QRect(710, 270, 101, 31));
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(620, 330, 41, 21));
        label_19->setFont(font);
        testing_3 = new QTextEdit(centralwidget);
        testing_3->setObjectName(QString::fromUtf8("testing_3"));
        testing_3->setGeometry(QRect(680, 320, 161, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1032, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "IP :", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "NETWORK CONFIGURATIONS", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "DATA BITS :", nullptr));
        DATABIT->setItemText(0, QCoreApplication::translate("MainWindow", "8", nullptr));
        DATABIT->setItemText(1, QCoreApplication::translate("MainWindow", "7", nullptr));

        BAUD->setItemText(0, QCoreApplication::translate("MainWindow", "115200", nullptr));
        BAUD->setItemText(1, QCoreApplication::translate("MainWindow", "9600", nullptr));
        BAUD->setItemText(2, QCoreApplication::translate("MainWindow", "4800", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "BAUD :", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "SERIAL LINE :", nullptr));
        OPENBUTTON->setText(QCoreApplication::translate("MainWindow", "OPEN", nullptr));
        STOPBITS->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        STOPBITS->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));

        label_12->setText(QCoreApplication::translate("MainWindow", "Status :", nullptr));
        CLOSEBUTTON->setText(QCoreApplication::translate("MainWindow", "CLOSE", nullptr));
        PARITY->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        PARITY->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));

        label_10->setText(QCoreApplication::translate("MainWindow", "PARITY :", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "NETMASK:", nullptr));
        UPDATE->setText(QCoreApplication::translate("MainWindow", "UPDATE", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "STOP BITS :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Status :", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "GATEWAY:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "COM :", nullptr));
        bt_refresh->setText(QCoreApplication::translate("MainWindow", "REFRESH", nullptr));
        NETMASK->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">255.255.255.0</p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "MODBUS GATEWAY PORT CONFIGURATIONS", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "PORT:", nullptr));
        BAUD_2->setItemText(0, QCoreApplication::translate("MainWindow", "PORT 1", nullptr));
        BAUD_2->setItemText(1, QCoreApplication::translate("MainWindow", "PORT 2", nullptr));
        BAUD_2->setItemText(2, QCoreApplication::translate("MainWindow", "PORT 3", nullptr));
        BAUD_2->setItemText(3, QCoreApplication::translate("MainWindow", "PORT 4", nullptr));

        label_15->setText(QCoreApplication::translate("MainWindow", "BAUD :", nullptr));
        BAUD_3->setItemText(0, QCoreApplication::translate("MainWindow", "9600", nullptr));
        BAUD_3->setItemText(1, QCoreApplication::translate("MainWindow", "4800", nullptr));
        BAUD_3->setItemText(2, QCoreApplication::translate("MainWindow", "115200", nullptr));

        label_16->setText(QCoreApplication::translate("MainWindow", "DATA BITS :", nullptr));
        DATABIT_2->setItemText(0, QCoreApplication::translate("MainWindow", "8", nullptr));
        DATABIT_2->setItemText(1, QCoreApplication::translate("MainWindow", "7", nullptr));

        label_17->setText(QCoreApplication::translate("MainWindow", "STOP BITS :", nullptr));
        STOPBITS_2->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        STOPBITS_2->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));

        label_18->setText(QCoreApplication::translate("MainWindow", "PARITY :", nullptr));
        PARITY_2->setItemText(0, QCoreApplication::translate("MainWindow", "NONE", nullptr));
        PARITY_2->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));

        UPDATE_2->setText(QCoreApplication::translate("MainWindow", "UPDATE", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Status :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
