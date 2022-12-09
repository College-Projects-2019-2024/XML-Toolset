#include <bits/stdc++.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Prettify_XML.h"
#include "compression.h"
#include <QFile>
#include <QTextStream>
#include<QMessageBox>
#include <QSaveFile>
#include <QFileDialog>
#include "vector"

ofstream fileOutput;
QFile mainfile;
QFile result;
vector<string>xml;
QString filename;

void setmainfile(){
    xml = get_xml(mainfile.fileName().toStdString());
}


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


    QTextStream in (&mainfile);
    ui->textBrowser->setText(in.readAll());
}


void MainWindow::on_pushButton_4_clicked()
{

    prettify(mainfile.fileName().toStdString(),"prettified.xml");


    filename = "prettified.xml";
    mainfile.setFileName(filename);
    if(!mainfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", mainfile.errorString());


    QTextStream in (&mainfile);
    ui->textBrowser_2->setText(in.readAll());

}


void MainWindow::on_pushButton_2_clicked()
{
    COLLEGEPROJECT_COMPRESSION_H::CompressXML(mainfile.fileName().toStdString(), "output.xml");


    filename = "output.xml";
    mainfile.setFileName(filename);
    if(!mainfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", mainfile.errorString());


    QTextStream in (&mainfile);
    ui->textBrowser_2->setText(in.readAll());

}


void MainWindow::on_pushButton_3_clicked()
{
    //mainfile.setFileName(filename);
//    if(!mainfile.open(QIODevice::ReadOnly))
//          QMessageBox::information(0,"info", mainfile.errorString());

    QString dir = QFileDialog::getExistingDirectory(this,tr("save file"));
    QFile::copy(mainfile.fileName(),dir+'/'+filename);

}

