#include <bits/stdc++.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <ostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Toolset.h"

Toolset *t;
ofstream fileoutputstream;

QString infilename;
QString outfilename;

QFile infile;
QFile outfile;

vector<string>result;
string r;


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

//choose file button
void MainWindow::on_pushButton_clicked()
{
    infilename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open File")
                    );

        infile.setFileName(infilename);
        if(!infile.open(QIODevice::ReadOnly))
              QMessageBox::information(0,"info", infile.errorString());

        t = new Toolset(infilename.toStdString());

        QTextStream in (&infile);
        ui->textBrowser->setText(in.readAll());


}



//prettify button
void MainWindow::on_pushButton_2_clicked()
{
    result = t->prettify();
    outfilename = "prettified.xml";
    fileoutputstream.open("prettified.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();
}


//compress button
void MainWindow::on_pushButton_4_clicked()
{
    r = t->CompressXML();
    outfilename = "compressed.xml";
    fileoutputstream.open("compressed.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());


    fileoutputstream << r << endl;
    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();

}

//decompress button
void MainWindow::on_pushButton_5_clicked()
{
    result = t->deCompressXML(infilename.toStdString());
    outfilename = "Decompressed.xml";
    fileoutputstream.open("Decompressed.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();

}

//save button
void MainWindow::on_pushButton_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("save file"));
    QFile::copy(outfile.fileName(),dir+'/'+outfilename);
}


void MainWindow::on_pushButton_6_clicked()
{
    r = t->MinifyXML();
    outfilename = "Minified.xml";
    fileoutputstream.open("Minified.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());


    fileoutputstream << r << endl;
    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();

}

