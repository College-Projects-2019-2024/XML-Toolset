/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1208, 813);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255,255,255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 10, 151, 51));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(1020, 110, 111, 51));
        pushButton_2->setAutoFillBackground(false);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(890, 10, 111, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(186, 186, 186);\n"
""));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1020, 170, 111, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1020, 230, 111, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(1020, 290, 111, 51));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(1020, 350, 111, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(1020, 410, 111, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(1020, 470, 111, 51));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(20, 110, 431, 561));
        textBrowser_2 = new QTextBrowser(centralwidget);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(460, 110, 531, 561));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Choose a file", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Prettify", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Save file", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Minify", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Detect errors", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Correct errors", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "ToJSON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
