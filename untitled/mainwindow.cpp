#include <bits/stdc++.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Prettify_XML.h"
#include "compression.h"
#include "Utility.h"
#include <QFile>
#include <QTextStream>
#include<QMessageBox>
#include <QSaveFile>
#include <QFileDialog>
#include "vector"

ofstream fileOutput;
QFile mainfile;
QFile result;
vector<Line>xml;
QString filename;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File")
                );

    mainfile.setFileName(filename);
    if(!mainfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", mainfile.errorString());

    xml = get_xml(mainfile.fileName().toStdString());


    QTextStream in (&mainfile);
    ui->textBrowser->setText(in.readAll());
}


void MainWindow::on_pushButton_4_clicked()
{

    prettify(xml,"prettified.xml");

    filename = "prettified.xml";
    result.setFileName(filename);
    if(!result.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info", result.errorString());


    QTextStream in (&result);
    ui->textBrowser_2->setText(in.readAll());

}


void MainWindow::on_pushButton_2_clicked()
{
//    COLLEGEPROJECT_COMPRESSION_H::CompressXML(xml, "output.xml");

//    filename = "output.xml";
//    result.setFileName(filename);
//    if(!result.open(QIODevice::ReadOnly))
//          QMessageBox::information(0,"info", result.errorString());


//    QTextStream in (&result);
//    ui->textBrowser_2->setText(in.readAll());

}


void MainWindow::on_pushButton_3_clicked()
{
    //mainfile.setFileName(filename);
//    if(!mainfile.open(QIODevice::ReadOnly))
//          QMessageBox::information(0,"info", mainfile.errorString());

    QString dir = QFileDialog::getExistingDirectory(this,tr("save file"));
    QFile::copy(result.fileName(),dir+'/'+filename);

}

